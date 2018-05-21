//
//  config.h
//  example-simple
//
//  Created by Hana on 2018/04/25.
//
//

#ifndef config_h
#define config_h

struct vbo_count_t {
    int num;
    int vertex = 0;
    int color = 0;
    int index = 0;
};

constexpr int VBOLINE_NUM_MAX = 512;
constexpr int VBOCIRCLE_NUM_MAX = 512;
constexpr int VBOTRIANGLE_NUM_MAX = 512;
constexpr int VBORECTANGLE_NUM_MAX = 512;
constexpr int VBOARC_NUM_MAX = 512;
constexpr int VBOWAVE_NUM_MAX = 512;

#endif /* config_h */
