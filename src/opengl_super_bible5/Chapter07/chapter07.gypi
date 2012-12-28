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
      ],
    }],
  ],
}

# Local Variables:
# tab-width:2
# indent-tabs-mode:nil
# End:
# vim: set expandtab tabstop=2 shiftwidth=2:
