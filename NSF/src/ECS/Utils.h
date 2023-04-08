#pragma once

#include <type_traits>

namespace NSF {
	class Component;

	template<class T>
	concept IsComponent = std::is_base_of<Component, T>::value;
}

