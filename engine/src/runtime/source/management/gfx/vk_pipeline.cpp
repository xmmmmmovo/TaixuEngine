/**
 * @file vk_pipeline.cpp
 * @author xmmmmmovo (ma_fivezha@163.com)
 * @brief
 * @date 2024-11-25
 *
 * Copyright (c) 2024 xmmmmmovo
 *
 */

#include "vk_pipeline.hpp"

#include "taixu/common/log/logger.hpp"
#include "vk_shader.hpp"


TX_NAMESPACE_BEGIN


vk::ShaderStageFlagBits mappingTXShaderStage(EnumShaderStage stage) noexcept {
    switch (stage) {
        case EnumShaderStage::FRAGMENT:
            return vk::ShaderStageFlagBits::eFragment;
        case EnumShaderStage::VERTEX:
            return vk::ShaderStageFlagBits::eVertex;
        case EnumShaderStage::GEOMETRY:
            return vk::ShaderStageFlagBits::eGeometry;
        case EnumShaderStage::COMPUTE:
            return vk::ShaderStageFlagBits::eCompute;
    }
    return vk::ShaderStageFlagBits::eVertex;
}

VulkanPipeline VulkanPipeline::createQuadPipeline(vk::raii::Device const&     device,
                                                  vk::raii::RenderPass const& render_pass, vk::Extent2D const& extent,
                                                  TXPipelineCreateInfo const& info) noexcept {
    tx_vector<vk::PipelineShaderStageCreateInfo> shader_stages(info.shaders.size());
    for (std::size_t i = 0; i < info.shaders.size(); ++i) {
        std::shared_ptr<VulkanShaderModule> shader =
                std::static_pointer_cast<VulkanShaderModule>(info.shaders[i].shader_module);
        shader_stages[i]
                .setStage(mappingTXShaderStage(info.shaders[i].stage))
                .setModule(*shader->getVulkanShaderModuleule())
                .setPName(shader->name().data());
    }

    vk::PipelineVertexInputStateCreateInfo vertex_input_state_info{};

    vk::PipelineInputAssemblyStateCreateInfo input_assembly_info{};
    input_assembly_info.setTopology(vk::PrimitiveTopology::eTriangleList).setPrimitiveRestartEnable(VK_FALSE);

    vk::Viewport viewport{};
    viewport.setX(0.0f)
            .setY(0.0f)
            .setWidth(static_cast<float>(extent.width))
            .setHeight(static_cast<float>(extent.height))
            .setMinDepth(0.0f)
            .setMaxDepth(1.0f);

    vk::Rect2D scissor{};
    scissor.setOffset({0, 0}).setExtent(extent);

    vk::PipelineViewportStateCreateInfo viewport_state_info{};
    viewport_state_info.setViewportCount(1).setPViewports(&viewport).setScissorCount(1).setPScissors(&scissor);

    vk::PipelineRasterizationStateCreateInfo rasterizer_info{};
    rasterizer_info.setDepthClampEnable(VK_FALSE)
            .setRasterizerDiscardEnable(VK_FALSE)
            .setPolygonMode(vk::PolygonMode::eFill)
            .setLineWidth(1.0f)
            .setFrontFace(vk::FrontFace::eCounterClockwise)
            .setCullMode(vk::CullModeFlagBits::eBack)
            .setDepthBiasEnable(VK_FALSE);

    // msaa
    vk::PipelineMultisampleStateCreateInfo multisampling_info{};
    multisampling_info.setSampleShadingEnable(VK_FALSE)
            .setRasterizationSamples(vk::SampleCountFlagBits::e1)
            .setMinSampleShading(1.0f)
            .setAlphaToCoverageEnable(VK_FALSE)
            .setAlphaToOneEnable(VK_FALSE);

    vk::PipelineColorBlendAttachmentState color_blend_attachment{};
    color_blend_attachment
            .setColorWriteMask(vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
                               vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA)
            .setBlendEnable(VK_FALSE);


    vk::PipelineColorBlendStateCreateInfo color_blending_info{};
    color_blending_info.setLogicOpEnable(VK_FALSE).setAttachmentCount(1).setPAttachments(&color_blend_attachment);

    std::shared_ptr<VulkanPipelineLayout> pipeline_layout =
            std::static_pointer_cast<VulkanPipelineLayout>(info.pipeline_layout);

    vk::GraphicsPipelineCreateInfo pipeline_info{};
    pipeline_info.setStages(shader_stages)
            .setPVertexInputState(&vertex_input_state_info)
            .setPInputAssemblyState(&input_assembly_info)
            .setPTessellationState(nullptr)
            .setPViewportState(&viewport_state_info)
            .setPRasterizationState(&rasterizer_info)
            .setPMultisampleState(&multisampling_info)
            .setPDepthStencilState(nullptr)
            .setPColorBlendState(&color_blending_info)
            .setPDynamicState(nullptr)
            .setLayout(*pipeline_layout->pipeline_layout)
            .setRenderPass(*render_pass)
            .setSubpass(0);

    auto pipeline = device.createGraphicsPipeline(nullptr, pipeline_info);
    if (!pipeline.has_value()) {
        ERROR_LOG("Failed to create graphics pipeline: {}", vk::to_string(pipeline.error()));
        return {};
    }

    VulkanPipeline vk_pipeline{};
    vk_pipeline._pipeline = std::move(pipeline.value());
    return vk_pipeline;
}

TX_NAMESPACE_END
