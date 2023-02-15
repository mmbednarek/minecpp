#pragma once
#include <minecpp/proto/common/v1/Vector.pb.h>

namespace minecpp::math {

template<typename TValue, int CCount>
struct ProtoVector
{};

template<>
struct ProtoVector<double, 2>
{
   using Type = proto::common::v1::Vector2;
};

template<>
struct ProtoVector<float, 2>
{
   using Type = proto::common::v1::Vector2f;
};

template<>
struct ProtoVector<int, 2>
{
   using Type = proto::common::v1::Vector2i;
};

template<>
struct ProtoVector<double, 3>
{
   using Type = proto::common::v1::Vector3;
};

template<>
struct ProtoVector<float, 3>
{
   using Type = proto::common::v1::Vector3f;
};

template<>
struct ProtoVector<int, 3>
{
   using Type = proto::common::v1::Vector3i;
};

}// namespace minecpp::math
