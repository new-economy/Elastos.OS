
#include "Elastos.Droid.App.h"
#include "Elastos.Droid.Utility.h"
#include "elastos/droid/webkit/native/content/browser/input/SelectPopupDialog.h"
#include "elastos/droid/webkit/native/content/browser/input/SelectPopupAdapter.h"
#include "elastos/droid/webkit/native/content/browser/ContentViewCore.h"

using Elastos::Droid::App::IAlertDialogBuilder;
using Elastos::Droid::App::IDialog;
using Elastos::Droid::App::EIID_IDialog;
using Elastos::Droid::Content::IDialogInterface;
using Elastos::Droid::Content::EIID_IDialogInterface;
using Elastos::Droid::Content::EIID_IDialogInterfaceOnCancelListener;
using Elastos::Droid::Content::EIID_IDialogInterfaceOnClickListener;
using Elastos::Droid::Widget::IAbsListView;
using Elastos::Droid::Widget::EIID_IAbsListView;
using Elastos::Droid::Widget::EIID_IAdapterViewOnItemClickListener;
using Elastos::Droid::Webkit::Content::Browser::ContentViewCore;
using Elastos::Droid::View::IView;
using Elastos::Droid::View::EIID_IView;
using Elastos::Droid::Utility::ISparseBooleanArray;

namespace Elastos {
namespace Droid {
namespace Webkit {
namespace Content {
namespace Browser {
namespace Input {

//==================================================================
//      SelectPopupDialog::OkDialogInterfaceOnClickListener
//==================================================================

CAR_INTERFACE_IMPL(SelectPopupDialog::OkDialogInterfaceOnClickListener, Object, IDialogInterfaceOnClickListener);

SelectPopupDialog::OkDialogInterfaceOnClickListener::OkDialogInterfaceOnClickListener(
    /* [in] */ SelectPopupDialog* owner,
    /* [in] */ IListView* listView)
    : mOwner(owner)
    , mListView(listView)
{
}

ECode SelectPopupDialog::OkDialogInterfaceOnClickListener::OnClick(
    /* [in] */ IDialogInterface* dialog,
    /* [in] */ Int32 which)
{
    mOwner->mContentViewCore->SelectPopupMenuItems(mOwner->GetSelectedIndices(mListView));
    return NOERROR;
}

//==================================================================
//     SelectPopupDialog::CancelDialogInterfaceOnClickListener
//==================================================================

CAR_INTERFACE_IMPL(SelectPopupDialog::CancelDialogInterfaceOnClickListener, Object, IDialogInterfaceOnClickListener);

SelectPopupDialog::CancelDialogInterfaceOnClickListener::CancelDialogInterfaceOnClickListener(
    /* [in] */ SelectPopupDialog* owner)
    : mOwner(owner)
{
}

ECode SelectPopupDialog::CancelDialogInterfaceOnClickListener::OnClick(
    /* [in] */ IDialogInterface* dialog,
    /* [in] */ Int32 which)
{
    mOwner->mContentViewCore->SelectPopupMenuItems(NULL);
    return NOERROR;
}

//==================================================================
//     SelectPopupDialog::InnerAdapterViewOnItemClickListener
//==================================================================

CAR_INTERFACE_IMPL(SelectPopupDialog::InnerAdapterViewOnItemClickListener, Object, IAdapterViewOnItemClickListener);

SelectPopupDialog::InnerAdapterViewOnItemClickListener::InnerAdapterViewOnItemClickListener(
    /* [in] */ SelectPopupDialog* owner,
    /* [in] */ IListView* listView)
    : mOwner(owner)
    , mListView(listView)
{
}

ECode SelectPopupDialog::InnerAdapterViewOnItemClickListener::OnItemClick(
    /* [in] */ IAdapterView* parent,
    /* [in] */ IView* v,
    /* [in] */ Int32 position,
    /* [in] */ Int64 id)
{
    mOwner->mContentViewCore->SelectPopupMenuItems(mOwner->GetSelectedIndices(mListView));
    AutoPtr<IDialogInterface> dialog = IDialogInterface::Probe(mOwner->mListBoxPopup);
    dialog->Dismiss();
    return NOERROR;
}

//==================================================================
//     SelectPopupDialog::InnerDialogInterfaceOnCancelListener
//==================================================================

CAR_INTERFACE_IMPL(SelectPopupDialog::InnerDialogInterfaceOnCancelListener, Object, IDialogInterfaceOnCancelListener);

SelectPopupDialog::InnerDialogInterfaceOnCancelListener::InnerDialogInterfaceOnCancelListener(
    /* [in] */ SelectPopupDialog* owner)
    : mOwner(owner)
{
}

ECode SelectPopupDialog::InnerDialogInterfaceOnCancelListener::OnCancel(
    /* [in] */ IDialogInterface* dialog)
{
    mOwner->mContentViewCore->SelectPopupMenuItems(NULL);
    return NOERROR;
}

//==================================================================
//                      SelectPopupDialog
//==================================================================

static AutoPtr< ArrayOf<Int32> > SELECT_DIALOG_ATTRS_Init()
{
    AutoPtr< ArrayOf<Int32> > array = ArrayOf<Int32>::Alloc(2);
    // TODO
    // (*array)[0] = R::attr::select_dialog_multichoice;
    // (*array)[1] = R::attr::select_dialog_singlechoice;
    return array;
}

const AutoPtr< ArrayOf<Int32> > SelectPopupDialog::SELECT_DIALOG_ATTRS = SELECT_DIALOG_ATTRS_Init();

SelectPopupDialog::SelectPopupDialog(
    /* [in] */ ContentViewCore* contentViewCore,
    /* [in] */ IList* items,
    /* [in] */ Boolean multiple,
    /* [in] */ ArrayOf<Int32>* selected)
    : mContentViewCore(contentViewCore)
    , mContext(mContentViewCore->GetContext())
{
    AutoPtr<IListView> listView;
    assert(0);
    // TODO
    // CListView::New(mContext, (IListView**)&listView);
    AutoPtr<IAbsListView> absListView = IAbsListView::Probe(listView);
    absListView->SetCacheColorHint(0);
    AutoPtr<IAlertDialogBuilder> b;
    assert(0);
    // TODO
    // CAlertDialogBuilder::New(mContext, (IAlertDialogBuilder**)&b);
    AutoPtr<IView> _view = IView::Probe(listView);
    b->SetView(_view);
    b->SetCancelable(TRUE);
    b->SetInverseBackgroundForced(TRUE);

    if (multiple) {
        AutoPtr<IDialogInterfaceOnClickListener> okListener =  new OkDialogInterfaceOnClickListener(this, listView);
        assert(0);
        // TODO
        // b->SetPositiveButton(android::R::string::ok, okListener);
        AutoPtr<IDialogInterfaceOnClickListener> cancelListener = new CancelDialogInterfaceOnClickListener(this);
        assert(0);
        // TODO
        // b->SetNegativeButton(android::R::string::cancel, cancelListener);
    }

    b->Create((IAlertDialog**)&mListBoxPopup);
    const AutoPtr<SelectPopupAdapter> adapter;// TODO = new SelectPopupAdapter(
            // mContext, GetSelectDialogLayout(multiple), items);
    assert(0);
    // TODO
    // listView->SetAdapter(adapter);
    // listView->SetFocusableInTouchMode(TRUE);

    if (multiple) {
        AutoPtr<IAbsListView> absListView = IAbsListView::Probe(listView);
        absListView->SetChoiceMode(IAbsListView::CHOICE_MODE_MULTIPLE);
        for (Int32 i = 0; i < selected->GetLength(); ++i) {
            absListView->SetItemChecked((*selected)[i], TRUE);
        }
    }
    else {
        AutoPtr<IAbsListView> absListView = IAbsListView::Probe(listView);
        absListView->SetChoiceMode(IAbsListView::CHOICE_MODE_SINGLE);
        AutoPtr<IAdapterViewOnItemClickListener> listener = new InnerAdapterViewOnItemClickListener(this, listView);
        assert(0);
        // TODO
        // listView->SetOnItemClickListener(listener);
        if (selected->GetLength() > 0) {
            assert(0);
            // TODO
            // listView->SetSelection((*selected)[0]);
            // listView->SetItemChecked((*selected)[0], TRUE);
        }
    }

    AutoPtr<IDialogInterfaceOnCancelListener> listener = new InnerDialogInterfaceOnCancelListener(this);
    AutoPtr<IDialog> _dialog = IDialog::Probe(mListBoxPopup);
    _dialog->SetOnCancelListener(THIS_PROBE(IDialogInterfaceOnCancelListener));
}

Int32 SelectPopupDialog::GetSelectDialogLayout(
    /* [in] */ Boolean isMultiChoice)
{
    Int32 resourceId;
    AutoPtr<ITypedArray> styledAttributes;
    assert(0);
    // TODO
    // mContext->ObtainStyledAttributes(
    //         R::style::SelectPopupDialog, SELECT_DIALOG_ATTRS,
    //         (ITypedArray**)&styledAttributes);
    styledAttributes->GetResourceId(isMultiChoice ? 0 : 1, 0, &resourceId);
    styledAttributes->Recycle();

    return resourceId;
}

AutoPtr< ArrayOf<Int32> > SelectPopupDialog::GetSelectedIndices(
    /* [in] */ IListView* listView)
{
    AutoPtr<ISparseBooleanArray> sparseArray;
    AutoPtr<IAbsListView> absListView = IAbsListView::Probe(listView);
    assert(0);
    // TODO
    // absListView->GetCheckedItemPositions((ISparseBooleanArray**)&sparseArray);
    Int32 selectedCount = 0;
    Int32 size;
    sparseArray->GetSize(&size);
    for (Int32 i = 0; i < size; ++i) {
        Boolean bFlag;
        sparseArray->ValueAt(i, &bFlag);
        if (bFlag) {
            selectedCount++;
        }
    }

    AutoPtr< ArrayOf<Int32> > indices = ArrayOf<Int32>::Alloc(selectedCount);
    sparseArray->GetSize(&size);
    for (Int32 i = 0, j = 0; i < size; ++i) {
        Boolean bFlag;
        sparseArray->ValueAt(i, &bFlag);
        if (bFlag) {
            Int32 value;
            sparseArray->KeyAt(i, &value);
            (*indices)[j++] = value;
        }
    }

    return indices;
}

//@Override
void SelectPopupDialog::Show()
{
    AutoPtr<IDialog> dialog = IDialog::Probe(mListBoxPopup);
    dialog->Show();
}

//@Override
void SelectPopupDialog::Hide()
{
    AutoPtr<IDialog> dialog = IDialog::Probe(mListBoxPopup);
    dialog->Cancel();
}

} // namespace Input
} // namespace Browser
} // namespace Content
} // namespace Webkit
} // namespace Droid
} // namespace Elastos
