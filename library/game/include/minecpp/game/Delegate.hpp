#pragma once

#include <minecpp/signal/Delegate.hpp>

#include <optional>

namespace minecpp::game {

template<typename... TArgs>
using Delegate = signal::Delegate<TArgs...>;

}// namespace minecpp::game