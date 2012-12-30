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
          'target_name': 'chapter07_texturerect',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'texturerect/SphereWorld.cpp',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'texturerect/Marble.tga',
                'texturerect/Marslike.tga',
                'texturerect/MoonLike.tga',
                'texturerect/OpenGL-Logo.tga',
                'texturerect/RectReplace.fp',
                'texturerect/RectReplace.vp',
              ],
            },
          ],
        },
        {
          'target_name': 'chapter07_cubemapped',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'cubemapped/cubemap.cpp',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'cubemapped/neg_x.tga',
                'cubemapped/neg_y.tga',
                'cubemapped/neg_z.tga',
                'cubemapped/pos_x.tga',
                'cubemapped/pos_y.tga',
                'cubemapped/pos_z.tga',
                'cubemapped/Reflection.fp',
                'cubemapped/Reflection.vp',
                'cubemapped/SkyBox.fp',
                'cubemapped/SkyBox.vp',
              ],
            },
          ],
        },
        {
          'target_name': 'chapter07_multitexture',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'multitexture/multitexture.cpp',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'multitexture/neg_x.tga',
                'multitexture/neg_y.tga',
                'multitexture/neg_z.tga',
                'multitexture/pos_x.tga',
                'multitexture/pos_y.tga',
                'multitexture/pos_z.tga',
                'multitexture/Reflection.fp',
                'multitexture/Reflection.vp',
                'multitexture/SkyBox.fp',
                'multitexture/SkyBox.vp',
                'multitexture/tarnish.tga',
              ],
            },
          ],
        },
        {
          'target_name': 'chapter07_pointsprites',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'pointsprites/pointsprites.cpp',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'pointsprites/SpaceFlight.fp',
                'pointsprites/SpaceFlight.vp',
                'pointsprites/star.tga',
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
