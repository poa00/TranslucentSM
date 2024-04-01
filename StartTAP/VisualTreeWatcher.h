#pragma once
#include "framework.h"

struct VisualTreeWatcher : winrt::implements<VisualTreeWatcher, IVisualTreeServiceCallback2, winrt::non_agile>
{
public:
	VisualTreeWatcher(winrt::com_ptr<IUnknown> site);
	VisualTreeWatcher(const VisualTreeWatcher&) = delete;
	VisualTreeWatcher& operator=(const VisualTreeWatcher&) = delete;

	VisualTreeWatcher(VisualTreeWatcher&&) = delete;
	VisualTreeWatcher& operator=(VisualTreeWatcher&&) = delete;
private:
	HRESULT STDMETHODCALLTYPE OnVisualTreeChange(ParentChildRelation relation, VisualElement element, VisualMutationType mutationType) override;
	HRESULT STDMETHODCALLTYPE OnElementStateChanged(InstanceHandle element, VisualElementState elementState, LPCWSTR context) noexcept override;
	template<typename T>
	T FromHandle(InstanceHandle handle)
	{
		IInspectable obj;
		winrt::check_hresult(m_XamlDiagnostics->GetIInspectableFromHandle(handle, reinterpret_cast<::IInspectable**>(winrt::put_abi(obj))));

		return obj.as<T>();
	}

	winrt::com_ptr<IXamlDiagnostics> m_XamlDiagnostics;
};