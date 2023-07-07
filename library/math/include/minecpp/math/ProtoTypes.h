#pragma once
#include <minecpp/proto/common/Vector.pb.h>

namespace minecpp::math {

template<typename TValue, int CCount>
struct ProtoVector
{};

template<>
struct ProtoVector<double, 2>
{
   using Type = proto::common::Vector2;
};

template<>
struct ProtoVector<float, 2>
{
   using Type = proto::common::Vector2f;
};

template<>
struct ProtoVector<int, 2>
{
   using Type = proto::common::Vector2i;
};

template<>
struct ProtoVector<double, 3>
{
   using Type = proto::common::Vector3;
};

template<>
struct ProtoVector<float, 3>
{
   using Type = proto::common::Vector3f;
};

template<>
struct ProtoVector<short, 3>
{
   using Type = proto::common::Vector3i;// Proto doesn't support i16
};

template<>
struct ProtoVector<int, 3>
{
   using Type = proto::common::Vector3i;
};

template<>
struct ProtoVector<std::int64_t, 3>
{
   using Type = proto::common::Vector3l;
};

}// namespace minecpp::math
