#pragma once

#include <string>

namespace ooe
{
	class iWorld
	{

	public:
		virtual ~iWorld() {}

		virtual void update() = 0;
		virtual void init() = 0;

		void setTag(std::string name) {tag_ = name; }
		std::string tag() const { return tag_; }

	protected:
		std::string tag_;
	};

}