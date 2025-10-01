
#include "dependencies/xproperty/source/xcore/my_properties.h"

namespace xresource
{
    //
    // We create properties for the particular resource reference
    //
    template< type_guid T_TYPE_GUID_V >
    struct property_ref_friend
    {
        XPROPERTY_DEF
        ("RscRef", xresource::def_guid<T_TYPE_GUID_V>
        , obj_member
            < "InstanceGuid"
            , +[](xresource::def_guid<T_TYPE_GUID_V>& O) ->auto& { return O.m_Instance.m_Value; }
            , member_help<"This is the instance GUID"
            >>
        , obj_member
            < "TypeGuid"
            , +[](xresource::def_guid<T_TYPE_GUID_V>& O) ->auto& { return O.m_Type.m_Value; }
            , member_help<"This is the type GUID"
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
