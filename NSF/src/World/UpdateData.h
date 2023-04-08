#pragma once

#include "../World/ITime.h"

namespace NSF {
	struct UpdateData {
		const ITime& time;

		UpdateData(const ITime* time) : time(*time) {}
	};
}
