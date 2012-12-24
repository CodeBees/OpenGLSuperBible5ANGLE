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
          'target_name': 'chapter06_shadedtriangle',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'ShadedTriangle/ShadedTriangle.cpp',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'ShadedTriangle/ShadedIdentity.fp',
                'ShadedTriangle/ShadedIdentity.vp',
              ],
            },
          ],
        },
        {
          'target_name': 'chapter06_provokingvertex',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'provokingvertex/provokingvertex.cpp',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'provokingvertex/provokingvertex.fp',
                'provokingvertex/provokingvertex.vp',
              ],
            },
          ],
        },
        {
          'target_name': 'chapter06_flatshader',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'flatshader/flatshader.cpp',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'flatshader/flatshader.fp',
                'flatshader/flatshader.vp',
              ],
            },
          ],
        },
        {
          'target_name': 'chapter06_diffuselight',
          'type': 'executable',
          'dependencies': [
            '<(DEPTH)/third_party/esGLUT/esGLUT.gyp:esGLUT',
            'gltools',
          ],
          'sources': [
            'diffuselight/diffuselight.cpp',
          ],
          'copies': [
            {
              'destination': '<(PRODUCT_DIR)',
              'files': [
                'diffuselight/diffuselight.fp',
                'diffuselight/diffuselight.vp',
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