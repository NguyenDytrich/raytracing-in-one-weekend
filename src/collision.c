#include "collision.h"
#include "mymem.h"

void set_face_normal(ray r, vec3 outward_normal, hit *hit)
{
  double dot = dot_vec3(*(r.direction), outward_normal);
  hit->front_face = dot < 0;
  if (hit->front_face)
  {
    hit->normal = outward_normal;
  }
  else
  {
    // Invert the normal
    mult_vec3(outward_normal, -1, &(hit->normal));
  }
}

bool __hit_sphere(void *_s, ray r, double ray_tmin, double ray_tmax, hit *hit_out)
{
  sphere *s = (sphere *)_s;
  vec3 oc;

  sub_vec3(*(r.origin), s->center, &oc);
  double a = sqr_len_vec3(*(r.direction));             // V * V == len(V)**2
  double hb = dot_vec3(oc, *(r.direction));            // 2h
  double c = sqr_len_vec3(oc) - s->radius * s->radius; // V * V == len(V)**2
  double discriminant = hb * hb - a * c;

  if (discriminant < 0)
    return false;

  // Find the square root in the acceptable range
  // Since the equation is quadratic, we check +/-
  double sqrtd = sqrt(discriminant);
  double root = (-hb - sqrtd) / a;
  if (root <= ray_tmin || root >= ray_tmax)
  {
    root = (-hb + sqrtd) / a;
    if (root <= ray_tmin || root >= ray_tmax)
    {
      return false;
    }
  }
  hit_out->t = root;
  ray_at(r, hit_out->t, &(hit_out->p));
  sub_vec3(hit_out->p, s->center, &(hit_out->normal));
  div_vec3(hit_out->normal, 0.5, &(hit_out->normal));

  vec3 outward_normal;
  sub_vec3(hit_out->p, s->center, &outward_normal);
  div_vec3(outward_normal, s->radius, &outward_normal);
  set_face_normal(r, outward_normal, hit_out);

  return true;
}

hittable new_sphere(point3 center, double radius)
{
  // !!! This is a memory leak
  // But don't need to fix for now
  sphere *s = (sphere *)my_malloc(sizeof(sphere));
  s->center = center;
  s->radius = radius;
  hittable obj = {
      &__hit_sphere,
      s};
  return obj;
}

void free_hittable(hittable obj)
{
  free(obj.data);
}

bool collision(hittable obj, ray r, double r_tmin, double r_tmax, hit *hit_out)
{
  return obj.__collision(obj.data, r, r_tmin, r_tmax, hit_out);
}

bool list_collision(hittable *objs, int obj_size, ray r, double r_tmin, double r_tmax, hit *hit_out)
{
  bool has_hit = false;
  double closest = r_tmax;
  for (int i = 0; i < obj_size / sizeof(hittable); i++)
  {
    if (collision(objs[i], r, r_tmin, closest, hit_out))
    {
      has_hit = true;
      closest = hit_out->t;
    }
  }
  return has_hit;
}