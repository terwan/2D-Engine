//Definition of iComponent type

#pragma once

namespace ooe
{
	struct iComponent
	{
		iComponent() : is_enabled_(true){}
		virtual ~iComponent(){}

		bool is_enabled_;
	};
}