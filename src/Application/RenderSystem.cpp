#include "RenderSystem.h"

void RenderSystem::update(std::shared_ptr<Entity> entity)
{
	//Continue only if entity has a model component
	if (entity->componentManager().getComponent<Model>() != nullptr) 
	{
		auto model = entity->componentManager().getComponent<Model>();
		auto position = entity->componentManager().getComponent<Transform>()->translation;
		//return if disabled
		if (!model->is_enabled_) return;

		//Simply draw model if no animation is present
		if (entity->componentManager().getComponent<Animation>() == nullptr) {
			//Determine whether to use quick draw algorithm or Transparency supported slower one
			if (model->quick_draw) gfx.quickdraw(position, model->sprite_id);
			else gfx.draw(position, model->sprite_id);
		} 
		else {
			auto animation = entity->componentManager().getComponent<Animation>();

			gfx.draw(position, model->sprite_id, animation->frame_dimension, animation->frame);

			//Every timetick move to the next animation time tick.
			//between time ticks, check whether animation should be enabled or not.
			if (Time::deltaTime() == 0) {
				++animation->frame;
			} else if (animation->frame < 1 || animation->frame > gfx.spriteFrames(model->sprite_id)) {
				animation->is_enabled_ = false;
			} else {
				animation->is_enabled_ = true;
			}
		}

		resetAnimation(entity);
	}
}

void RenderSystem::resetAnimation(std::shared_ptr<Entity> e)
{
	if (e->componentManager().getComponent<Animation>() != nullptr && !e->componentManager().getComponent<Animation>()->is_enabled_) {
		e->componentManager().getComponent<Animation>()->frame = 1;
	}
}