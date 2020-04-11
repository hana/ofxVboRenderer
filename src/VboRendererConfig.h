//
//  VboRendererConfig.h
//  example-simple
//
//  Created by Hana on 2018/04/25.
//
//

#pragma once

#ifndef VboRendererConfig_h
#define VboRendererConfig_h

struct vbo_count_t {
    int num;
    int vertex = 0;
    int color = 0;
    int index = 0;
};

constexpr std::size_t VBOLINE_NUM_MAX = 512;
constexpr std::size_t VBOCIRCLE_NUM_MAX = 512;
constexpr std::size_t VBOTRIANGLE_NUM_MAX = 512;
constexpr std::size_t VBORECTANGLE_NUM_MAX = 512;
constexpr std::size_t VBOARC_NUM_MAX = 512;
constexpr std::size_t VBOWAVE_NUM_MAX = 512;

#endif /* VboRendererConfig_h */
