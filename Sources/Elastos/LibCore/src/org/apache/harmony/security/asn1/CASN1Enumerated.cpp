
#include "CASN1Enumerated.h"
#include "CBerInputStream.h"
#include "Arrays.h"
#include "CoreUtils.h"

using Elastos::Core::CoreUtils;
using Elastos::Core::IArrayOf;
using Elastos::Utility::Arrays;
using Elastos::Utility::Arrays;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Security {
namespace Asn1 {

INIT_PROI_3 AutoPtr<IASN1Enumerated> CASN1Enumerated::sASN1 = Init();

CAR_OBJECT_IMPL(CASN1Enumerated)

CAR_INTERFACE_IMPL(CASN1Enumerated, ASN1Primitive, IASN1Enumerated)

AutoPtr<IASN1Enumerated> CASN1Enumerated::Init()
{
    return new CASN1Enumerated();
}

ECode CASN1Enumerated::GetInstance(
    /* [out] */ IASN1Enumerated** instance)
{
    VALIDATE_NOT_NULL(instance)
    *instance = sASN1;
    REFCOUNT_ADD(*instance)
    return NOERROR;
}

ECode CASN1Enumerated::Decode(
    /* [in] */ IBerInputStream* bis,
    /* [out] */ IInterface** object)
{
    bis->ReadEnumerated();

    if (((CBerInputStream*)bis)->mIsVerify) {
        return NOERROR;
    }
    return GetDecodedObject(bis, object);
}

ECode CASN1Enumerated::GetDecodedObject(
    /* [in] */ IBerInputStream* bis,
    /* [out, callee] */ IInterface** object)
{
    VALIDATE_NOT_NULL(object);
    AutoPtr<ArrayOf<Byte> > buffer;
    bis->GetBuffer((ArrayOf<Byte>**)&buffer);
    Int32 contentOffset, length;
    bis->GetContentOffset(&contentOffset);
    bis->GetLength(&length);

    AutoPtr<ArrayOf<Byte> > data;
    Arrays::CopyOfRange(buffer, contentOffset, contentOffset + length, (ArrayOf<Byte>**)&data);
    *object = CoreUtils::ConvertByteArray(data);
    REFCOUNT_ADD(*object);
    return NOERROR;
}

ECode CASN1Enumerated::EncodeContent(
    /* [in] */ IBerOutputStream* bos)
{
    return bos->EncodeInteger();
}

ECode CASN1Enumerated::SetEncodingContent(
    /* [in] */ IBerOutputStream* bos)
{
    AutoPtr<IInterface> content;
    bos->GetContent((IInterface**)&content);
    Int32 length;
    IArrayOf::Probe(content)->GetLength(&length);
    return bos->SetLength(length);
}

ECode CASN1Enumerated::constructor()
{
    return ASN1Primitive::constructor(IASN1Constants::TAG_ENUM);
}

} // namespace Asn1
} // namespace Security
} // namespace Harmony
} // namespace Apache
} // namespace Org

