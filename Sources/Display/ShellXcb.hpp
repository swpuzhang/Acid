#pragma once

#include <xcb/xcb.h>
#include <dlfcn.h>
#include "IShell.hpp"

namespace acid
{
	class FL_EXPORT MonitorXcb :
		public IMonitor
	{
	private:
		uint32_t m_width;
		uint32_t m_height;
	public:
		MonitorXcb(const uint32_t &width, const uint32_t &height) :
			IMonitor(),
			m_width(width),
			m_height(height)
		{
		}

		~MonitorXcb()
		{
		}

		uint32_t GetWidth() const override { return m_width; }

		uint32_t GetHeight() const override { return m_height; }
	};

	class ShellXcb :
		public IShell
	{
	private:
		xcb_connection_t *connection_;
		xcb_screen_t *screen_;
		xcb_window_t window_;
		xcb_atom_t wm_protocols_;
		xcb_atom_t wm_delete_window_;

		void *lib_handle_;
	public:
		ShellXcb();

		~ShellXcb();

		VkResult CreateSurface(VkInstance instance, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) override;

		void PollEvents() override;

		MessageResponse ShowMessageBox(const std::string &title, const std::string &message, const Message &type) override;

		void SetSize(const uint32_t &width, const uint32_t &height) override;

		void SetPosition(const uint32_t &x, const uint32_t &y) override;

		void SetShown(const uint32_t &shownFlags) override;

		void SetResizable(const bool &resizable) override;

		void SetTitle(const std::string &title) override;

		void SetIconImage(unsigned char *data, const uint32_t &width, const uint32_t &height) override;

		void SetCursorImage(unsigned char *data, const uint32_t &width, const uint32_t &height) override;

		void SetFullscreen(const std::shared_ptr<IMonitor> &monitor, const bool &fullscreen) override;

		void SetCursorMode(const CursorMode &mode) override;

		void SetCursorPosition(const uint32_t &x, const uint32_t &y) override;
	private:
		void HandleEvent(const xcb_generic_event_t *ev);

		void InitConnection();

		void LoadVk();

		void CreateDisplay();

		xcb_intern_atom_cookie_t intern_atom_cookie(xcb_connection_t *c, const char* s);

		xcb_atom_t intern_atom(xcb_connection_t *c, xcb_intern_atom_cookie_t cookie);

	};
}
