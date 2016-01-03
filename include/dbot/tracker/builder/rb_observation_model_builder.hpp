/*
 * This is part of the Bayesian Object Tracking (bot),
 * (https://github.com/bayesian-object-tracking)
 *
 * Copyright (c) 2015 Max Planck Society,
 * 				 Autonomous Motion Department,
 * 			     Institute for Intelligent Systems
 *
 * This Source Code Form is subject to the terms of the GNU General Public
 * License License (GNU GPL). A copy of the license can be found in the LICENSE
 * file distributed with this source code.
 */

/**
 * \file rb_observation_model_builder.hpp
 * \date November 2015
 * \author Jan Issac (jan.issac@gmail.com)
 */

#pragma once

#include <memory>

#include <Eigen/Dense>

#include <dbot/model/observation/rao_blackwell_observation_model.hpp>

namespace dbot
{

template <typename State>
class RbObservationModelBuilder
{
public:

    struct Parameters
    {
        struct Occlusion
        {
            double p_occluded_visible;
            double p_occluded_occluded;
            double initial_occlusion_prob;
        };

        struct Kinect
        {
            double tail_weight;
            double model_sigma;
            double sigma_factor;
        };

        Occlusion occlusion;
        Kinect kinect;
        double delta_time;
        int sample_count;
        bool use_custom_shaders;
        std::string vertex_shader_file;
        std::string fragment_shader_file;
        std::string geometry_shader_file;
    };

    typedef RbObservationModel<State> Model;

public:
    virtual std::shared_ptr<Model> build() const
    {
        std::shared_ptr<Model> model(create());
        return model;
    }

protected:
    virtual std::shared_ptr<Model> create() const = 0;
};

}