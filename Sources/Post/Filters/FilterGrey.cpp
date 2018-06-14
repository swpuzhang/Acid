#include "FilterGrey.hpp"

namespace fl
{
	FilterGrey::FilterGrey(const GraphicsStage &graphicsStage) :
		IPostFilter({"Shaders/Filters/Default.vert", "Shaders/Filters/Grey.frag"}, graphicsStage, {})
	{
	}

	FilterGrey::~FilterGrey()
	{
	}

	void FilterGrey::Render(const CommandBuffer &commandBuffer)
	{
		// Updates descriptors.
		m_descriptorSet.Push("writeColour", m_pipeline.GetTexture(2));
		m_descriptorSet.Push("samplerColour", m_pipeline.GetTexture(2));
		bool updateSuccess = m_descriptorSet.Update(m_pipeline);

		if (!updateSuccess)
		{
			return;
		}

		// Draws the object.
		m_pipeline.BindPipeline(commandBuffer);

		m_descriptorSet.BindDescriptor(commandBuffer);
		m_model->CmdRender(commandBuffer);
	}
}
