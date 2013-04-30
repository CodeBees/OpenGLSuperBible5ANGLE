# Copyright (c) 2010 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'targets': [
  ],
  'conditions': [
    ['OS=="win"', {
      'targets': [
        {
          'target_name': 'chapter08_pix_buffs',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'pix_buffs/pix_buffs.cpp',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'pix_buffs/blur.fs',
                'pix_buffs/blur.vs',
                'pix_buffs/marble.bmp',
              ],
            },
          ],
        },
        {
          'target_name': 'chapter08_fbo_drawbuffers',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'fbo_drawbuffers/fbo_drawbuffers.cpp',
            'fbo_drawbuffers/sbm.cpp',
            'fbo_drawbuffers/sbm.h',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'fbo_drawbuffers/LumLinear.data',
                'fbo_drawbuffers/LumSin.data',
                'fbo_drawbuffers/LumTan.data',
                'fbo_drawbuffers/marble.bmp',
                'fbo_drawbuffers/Marslike.bmp',
                'fbo_drawbuffers/MoonLike.bmp',
                'fbo_drawbuffers/multibuffer.fs',
                'fbo_drawbuffers/multibuffer.vs',
                'fbo_drawbuffers/multibuffer_frag_location.fs',
                'fbo_drawbuffers/ninja.sbm',
                'fbo_drawbuffers/ninjacomp.bmp',
              ],
            },
          ],
        },
      ],
    }],
  ],
}

# Local Variables:
# tab-width:2
# indent-tabs-mode:nil
# End:
# vim: set expandtab tabstop=2 shiftwidth=2:
