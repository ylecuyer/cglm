/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef cglm_affine_neon_h
#define cglm_affine_neon_h
#if defined(__ARM_NEON_FP)

#include "../../common.h"
#include "../intrin.h"

CGLM_INLINE
void
glm_mul_neon(mat4 m1, mat4 m2, mat4 dest) {
  /* D = R * L (Column-Major) */

  glmm_128 l0, l1, l2, l3, r0, r1, r2, r3, v0, v1, v2, v3;

  l0 = glmm_load(m1[0]);    r0 = glmm_load(m2[0]);
  l1 = glmm_load(m1[1]);    r1 = glmm_load(m2[1]);
  l2 = glmm_load(m1[2]);    r2 = glmm_load(m2[2]);
  l3 = glmm_load(m1[3]);    r3 = glmm_load(m2[3]);

  v0 = vmulq_f32(glmm_splat_x(r0), l0);
  v1 = vmulq_f32(glmm_splat_x(r1), l0);
  v2 = vmulq_f32(glmm_splat_x(r2), l0);
  v3 = vmulq_f32(glmm_splat_x(r3), l0);

  v0 = glmm_fmadd(glmm_splat_y(r0), l1, v0);
  v1 = glmm_fmadd(glmm_splat_y(r1), l1, v1);
  v2 = glmm_fmadd(glmm_splat_y(r2), l1, v2);
  v3 = glmm_fmadd(glmm_splat_y(r3), l1, v3);

  v0 = glmm_fmadd(glmm_splat_z(r0), l2, v0);
  v1 = glmm_fmadd(glmm_splat_z(r1), l2, v1);
  v2 = glmm_fmadd(glmm_splat_z(r2), l2, v2);
  v3 = glmm_fmadd(glmm_splat_z(r3), l2, v3);

  v3 = glmm_fmadd(glmm_splat_w(r3), l3, v3);

  glmm_store(dest[0], v0);
  glmm_store(dest[1], v1);
  glmm_store(dest[2], v2);
  glmm_store(dest[3], v3);
}

CGLM_INLINE
void
glm_mul_rot_neon(mat4 m1, mat4 m2, mat4 dest) {
  /* D = R * L (Column-Major) */

  glmm_128 l0, l1, l2, r0, r1, r2, v0, v1, v2;

  l0 = glmm_load(m1[0]);    r0 = glmm_load(m2[0]);
  l1 = glmm_load(m1[1]);    r1 = glmm_load(m2[1]);
  l2 = glmm_load(m1[2]);    r2 = glmm_load(m2[2]);

  v0 = vmulq_f32(glmm_splat_x(r0), l0);
  v1 = vmulq_f32(glmm_splat_x(r1), l0);
  v2 = vmulq_f32(glmm_splat_x(r2), l0);

  v0 = glmm_fmadd(glmm_splat_y(r0), l1, v0);
  v1 = glmm_fmadd(glmm_splat_y(r1), l1, v1);
  v2 = glmm_fmadd(glmm_splat_y(r2), l1, v2);

  v0 = glmm_fmadd(glmm_splat_z(r0), l2, v0);
  v1 = glmm_fmadd(glmm_splat_z(r1), l2, v1);
  v2 = glmm_fmadd(glmm_splat_z(r2), l2, v2);

  glmm_store(dest[0], v0);
  glmm_store(dest[1], v1);
  glmm_store(dest[2], v2);
  glmm_store(dest[3], glmm_load(m1[3]));
}

#endif
#endif /* cglm_affine_neon_h */
