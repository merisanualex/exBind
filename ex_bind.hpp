#pragma once

#include <type_traits>
#include <utility>

namespace ex
{
	namespace internal
	{
		template <typename T, typename ...Args>
		struct all_same_as;

		template <typename T, typename First>
		struct all_same_as<T, First>
		{
			static constexpr bool value = std::is_same<T, First>::value;
		};

		template <typename T, typename First, typename ...Rest>
		struct all_same_as<T, First, Rest...>
		{
			static constexpr bool value = std::is_same<T, First>::value && all_same_as<T, Rest...>::value;
		};

		struct ph_t
		{
			constexpr ph_t() = default;

			template <typename T>
			constexpr ph_t(T&&)
			{

			}
		};
	}

	constexpr auto ph = internal::ph_t{};

	template <typename ReturnType,
		typename ...Args,
		typename ...PHs
#ifdef EX_BIND_DIAGNOSTIC_ENABLE_IF
		,typename = typename std::enable_if<internal::all_same_as<const internal::ph_t&, PHs...>::value>::type
#endif
	>
	auto bind(ReturnType(*func)(Args...), PHs&&... placeHolders)
	{
#ifdef EX_BIND_DIAGNOSTIC_STATIC_ASSERT
		static_assert(internal::all_same_as<const internal::ph_t&, PHs...>::value, R"("ex::ph" is the only valid placeholder !)");
#endif

		return [func](Args&&... originalArgs, PHs&&... innerPlaceHolders)
		{
			return func(std::forward<Args>(originalArgs)...);
		};
	}
}
