#ifndef XRESOURCE_XPROPERTIES_BRIDGE_H
#define XRESOURCE_XPROPERTIES_BRIDGE_H
#pragma once

#include "dependencies/xproperty/source/xcore/my_properties.h"
#include "dependencies/xresource_mgr/source/xresource_mgr.h"

namespace xresource
{
    // Give properties to the type_guid
    struct type_guid_give_properties : type_guid
    {
        XPROPERTY_DEF
        ("type_guid", type_guid
        , obj_member < "Value"
            , &type_guid::m_Value
            , member_flags<flags::SHOW_READONLY>
            , member_ui<std::uint64_t>::drag_bar<0.f, 0, std::numeric_limits<std::uint64_t>::max(), "%llX">
            , member_help<"64bit Unique identifier for the resource type, this is how the system knows about this resource type. "
                          "This is part of the full 128bit which is the true unique ID of the resource"
            >>
        );
    };
    XPROPERTY_REG(type_guid_give_properties)

    // Give properties to the instance_guid
    struct instance_guid_give_properties : xresource::instance_guid
    {
        XPROPERTY_DEF
        ("instance_guid", xresource::instance_guid
        , obj_member < "Value"
            , &xresource::instance_guid::m_Value
            , member_flags<flags::SHOW_READONLY>
            , member_ui<std::uint64_t>::drag_bar<0.f, 0, std::numeric_limits<std::uint64_t>::max(), "%llX">
            , member_help<"64bit Unique identifier for the resource, this is how the system knows about this resource "
                          "This is part of the full 128bit which is the true unique ID of the resource"
            >>
        );
    };
    XPROPERTY_REG(instance_guid_give_properties)

    // Give properties to the instance_guid
    struct instance_guid_large_give_properties : xresource::instance_guid_large
    {
        XPROPERTY_DEF
        ("instance_guid", xresource::instance_guid_large
        , obj_member < "Low"
            , &xresource::instance_guid_large::m_Low
            , member_flags<flags::SHOW_READONLY>
            , member_ui<std::uint64_t>::drag_bar<0.f, 0, std::numeric_limits<std::uint64_t>::max(), "%llX">
            , member_help<"64bit Unique identifier for the resource, this is how the system knows about this resource "
                          "This is part of the full 128bit which is the true unique ID of the resource"
            >>
        , obj_member < "High"
            , &xresource::instance_guid_large::m_High
            , member_flags<flags::SHOW_READONLY>
            , member_ui<std::uint64_t>::drag_bar<0.f, 0, std::numeric_limits<std::uint64_t>::max(), "%llX">
            , member_help<"64bit Unique identifier for the resource, this is how the system knows about this resource "
                          "This is part of the full 128bit which is the true unique ID of the resource"
            >>
        );
    };
    XPROPERTY_REG(instance_guid_large_give_properties)

    //
    // We create properties for the particular resource reference
    //
    template< type_guid T_TYPE_GUID_V >
    struct property_ref_friend
    {
        inline static constexpr auto type_guid_filter_v = std::array{ T_TYPE_GUID_V };

        XPROPERTY_DEF
        ("RscRef", xresource::def_guid<T_TYPE_GUID_V>
        , obj_member
            < "FullGUID"
            , +[](xresource::def_guid<T_TYPE_GUID_V>& I, bool bRead, xresource::full_guid& xFullGuid )
            {
                if ( bRead )
                {
                    if (I.m_Instance.isPointer()) xFullGuid = xresource::g_Mgr.getFullGuid(I);
                    else                          xFullGuid = I;
                }
                else
                {
                    if (I.m_Instance.isPointer()) xresource::g_Mgr.ReleaseRef(I);
                    I.m_Instance = xFullGuid.m_Instance;
                }
            }
            , member_ui<xresource::full_guid>::type_filters<type_guid_filter_v>
            , member_help<"Full GUID used to serialize and Inspect our GUID"
            >>
        )
    };

    //
    // This allows the user to more easily register the reference with the property system
    // just need to create a global variable with this type
    //
    template<type_guid T_TYPE_GUID_V>
    using property_reg_t = decltype(property_ref_friend<T_TYPE_GUID_V>::PropertiesDefinition());

    //
    // Usually when registering a loader from the resource manager you need to register a few things as well
    // this is a convinient structure to do all the require registrations by creating an global variable
    // of this type.
    // Example:
    //      inline static auto s_MaterialRegistrations = xresource::common_registrations<xrsc::material_type_guid_v>{};
    //
    template<type_guid T_TYPE_GUID_V>
    struct common_registrations
    {
        xresource::loader_registration<T_TYPE_GUID_V> m_LoaderRegistration      = {};
        xresource::property_reg_t<T_TYPE_GUID_V>      m_PropertyRefRegistration = {};
    };
}
#endif
