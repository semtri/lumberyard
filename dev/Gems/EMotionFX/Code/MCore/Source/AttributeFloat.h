/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

// include the required headers
#include "StandardHeaders.h"
#include "Attribute.h"
#include "StringConversions.h"

namespace MCore
{
    /**
     * The float attribute class.
     * This attribute represents one float.
     */
    class MCORE_API AttributeFloat
        : public Attribute
    {
        friend class AttributeFactory;
    public:
        enum
        {
            TYPE_ID = 0x00000001
        };

        static AttributeFloat* Create(float value = 0.0f);

        // adjust values
        MCORE_INLINE float GetValue() const                         { return mValue; }
        MCORE_INLINE void SetValue(float value)                     { mValue = value; }

        MCORE_INLINE uint8* GetRawDataPointer()                     { return reinterpret_cast<uint8*>(&mValue); }
        MCORE_INLINE uint32 GetRawDataSize() const                  { return sizeof(float); }

        // overloaded from the attribute base class
        Attribute* Clone() const override                           { return AttributeFloat::Create(mValue); }
        Attribute* CreateInstance(void* destMemory) override        { return new(destMemory) AttributeFloat(); }
        const char* GetTypeString() const override                  { return "AttributeFloat"; }
        bool InitFrom(const Attribute* other) override;
        bool InitFromString(const AZStd::string& valueString) override
        {
            return AzFramework::StringFunc::LooksLikeFloat(valueString.c_str(), &mValue);
        }
        bool ConvertToString(AZStd::string& outString) const override      { outString = AZStd::string::format("%.8f", mValue); return true; }
        uint32 GetClassSize() const override                        { return sizeof(AttributeFloat); }
        uint32 GetDefaultInterfaceType() const override             { return ATTRIBUTE_INTERFACETYPE_FLOATSPINNER; }

    private:
        float   mValue;     /**< The float value. */

        uint32 GetDataSize() const override                         { return sizeof(float); }

        AttributeFloat()
            : Attribute(TYPE_ID)
            , mValue(0.0f)  {}
        AttributeFloat(float value)
            : Attribute(TYPE_ID)
            , mValue(value) {}
        ~AttributeFloat() {}

        // read from a stream
        bool ReadData(MCore::Stream* stream, MCore::Endian::EEndianType streamEndianType, uint8 version) override
        {
            MCORE_UNUSED(version);

            float streamValue;
            if (stream->Read(&streamValue, sizeof(float)) == 0)
            {
                return false;
            }

            Endian::ConvertFloat(&streamValue, streamEndianType);
            mValue = streamValue;
            return true;
        }
    };
}   // namespace MCore
