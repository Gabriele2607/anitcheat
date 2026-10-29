#include "Helpers/ViewCone.h"
#include "Config/Config.h"
#include <cassert>
#include <limits>
#include <sstream>
int main() {
 using awh::OutsideViewCone;
 assert(!OutsideViewCone(0, 1000, 0, 40, 160, 64));
 assert(OutsideViewCone(0, -1000, 0, 40, 160, 64));
 assert(!OutsideViewCone(180, -1000, 0, 40, 160, 64));
 assert(OutsideViewCone(180, 1000, 0, 40, 160, 64));
 assert(!OutsideViewCone(0, -50, 0, 40, 160, 64));
 assert(!OutsideViewCone(0, 0, 0, 40, 160, 64));
 assert(!OutsideViewCone(0, -1000, 0, 40, 360, 64));
 assert(!OutsideViewCone(359, 1000, 0, 40, 160, 64));
 assert(!OutsideViewCone(std::numeric_limits<float>::quiet_NaN(), -1000, 0, 40, 160, 64));
 // Hull crossing the cone edge remains visible.
 assert(!OutsideViewCone(0, 173.648f, 984.808f, 40, 160, 64));
 assert(OutsideViewCone(0, 0, 1000, 40, 160, 64));
 std::istringstream in("FovFilter 1\nFovDegrees 160\nFovNearDistance 64\nAutoUpdate 0\n");
 auto s=awh::ParseConfig(in); assert(s.FovFilter && s.FovDegrees==160 && !s.AutoUpdate);
 std::ostringstream out; awh::WriteConfig(out,s); std::istringstream again(out.str());
 auto t=awh::ParseConfig(again); assert(t.FovFilter && t.FovNearDistance==64 && !t.AutoUpdate);
 bool rejected=false; try {std::istringstream bad("FovDegrees 10"); awh::ParseConfig(bad);} catch(...) {rejected=true;}
 assert(rejected);
}
