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
          'target_name': 'chapter05_pyramid',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'Pyramid/Pyramid.cpp',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'Pyramid/stone.tga',
              ],
            },
          ],
        },
        {
          'target_name': 'chapter05_tunnel',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'Tunnel/Tunnel.cpp',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'Tunnel/brick.tga',
                'Tunnel/ceiling.tga',
                'Tunnel/floor.tga',
              ],
            },
          ],
        },
        {
          'target_name': 'chapter05_anisotropic',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'Anisotropic/Tunnel.cpp',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'Anisotropic/brick.tga',
                'Anisotropic/ceiling.tga',
                'Anisotropic/floor.tga',
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
