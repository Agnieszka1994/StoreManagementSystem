#pragma once
#include <sqlite_orm.h>
#define StorageType struct sqlite_orm::internal::storage_t<																		\
					struct sqlite_orm::internal::table_t<																		\
					struct User,struct sqlite_orm::internal::column_t<															\
					struct User,int,int const & (__thiscall User::*)(void)const ,												\
					void (__thiscall User::*)(int),																				\
					struct sqlite_orm::constraints::autoincrement_t,															\
					struct sqlite_orm::constraints::primary_key_t<> >,															\
					struct sqlite_orm::internal::column_t<																		\
					struct User,int,int const & (__thiscall User::*)(void)const ,												\
					void (__thiscall User::*)(int)>,struct sqlite_orm::internal::column_t<										\
					struct User,class std::basic_string<char,struct std::char_traits<char>,										\
					class std::allocator<char> >,class std::basic_string<char,													\
					struct std::char_traits<char>,class std::allocator<char> >													\
					const & (__thiscall User::*)(void)const ,																	\
					void (__thiscall User::*)(class std::basic_string<char,														\
					struct std::char_traits<char>,class std::allocator<char> >)>,												\
					struct sqlite_orm::internal::column_t<struct User,															\
					class std::basic_string<char,struct std::char_traits<char>,													\
					class std::allocator<char> >,																				\
					class std::basic_string<char, struct std::char_traits<char>,												\
					class std::allocator<char> > const & (__thiscall User::*)(void)const ,										\
					void (__thiscall User::*)(class std::basic_string<char,struct std::char_traits<char>,						\
					class std::allocator<char> >)> >,																			\
					struct sqlite_orm::internal::table_t<struct Product,														\
					struct sqlite_orm::internal::column_t<struct Product,														\
					int,int const & (__thiscall Product::*)(void)const ,void (__thiscall Product::*)(int),						\
					struct sqlite_orm::constraints::autoincrement_t,															\
					struct sqlite_orm::constraints::primary_key_t<> >,															\
					struct sqlite_orm::internal::column_t<struct Product,														\
					class std::basic_string<char,struct std::char_traits<char>,													\
					class std::allocator<char> >,class std::basic_string<char,struct std::char_traits<char>,					\
					class std::allocator<char> > const & (__thiscall Product::*)(void)const ,									\
					void (__thiscall Product::*)(class std::basic_string<char,struct std::char_traits<char>,					\
					class std::allocator<char> >)>,struct sqlite_orm::internal::column_t<										\
					struct Product,double,double const & (__thiscall Product::*)(void)const ,									\
					void (__thiscall Product::*)(double)>,struct sqlite_orm::internal::column_t<								\
					struct Product,int,int const & (__thiscall Product::*)(void)const ,											\
					void (__thiscall Product::*)(int)> >,struct sqlite_orm::internal::table_t<									\
					struct Order,struct sqlite_orm::internal::column_t<															\
					struct Order,int,int const & (__thiscall Order::*)(void)const ,												\
					void (__thiscall Order::*)(int),struct sqlite_orm::constraints::autoincrement_t,							\
					struct sqlite_orm::constraints::primary_key_t<> >,struct sqlite_orm::internal::column_t<					\
					struct Order,int,int const & (__thiscall Order::*)(void)const ,												\
					void (__thiscall Order::*)(int)>,struct sqlite_orm::internal::column_t<										\
					struct Order,int,int const & (__thiscall Order::*)(void)const ,												\
					void (__thiscall Order::*)(int)>,struct sqlite_orm::internal::column_t<										\
					struct Order,int,int const & (__thiscall Order::*)(void)const ,												\
					void (__thiscall Order::*)(int)>,struct sqlite_orm::internal::column_t<										\
					struct Order,class std::basic_string<char,struct std::char_traits<char>,									\
					class std::allocator<char> >,class std::basic_string<char,struct std::char_traits<char>,				    \
					class std::allocator<char> > const & (__thiscall Order::*)(void)const ,										\
					void (__thiscall Order::*)(class std::basic_string<char,struct std::char_traits<char>,					    \
					class std::allocator<char> >)> >,struct sqlite_orm::internal::table_t<struct UserType,					    \
					struct sqlite_orm::internal::column_t<struct UserType,int,int const & (__thiscall UserType::*)(void)const , \
					void (__thiscall UserType::*)(int),struct sqlite_orm::constraints::autoincrement_t,							\
					struct sqlite_orm::constraints::primary_key_t<> >,struct sqlite_orm::internal::column_t<					\
					struct UserType,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,	\
					class std::basic_string<char,struct std::char_traits<char>,													\
					class std::allocator<char> > const & (__thiscall UserType::*)(void)const ,									\
					void (__thiscall UserType::*)(class std::basic_string<char,struct std::char_traits<char>,					\
					class std::allocator<char> >),struct sqlite_orm::constraints::default_t<char const *> > > >