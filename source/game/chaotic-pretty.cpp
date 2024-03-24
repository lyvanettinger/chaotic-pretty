#include "core/device.hpp"
#include "rendering/renderer.hpp"

using namespace chap;

int main()
{
	Renderer* renderer = new Renderer;
	Device* device = new Device;

	while (!device->ShouldClose())
	{
		renderer->Render();
		device->Update();
	}

	delete renderer;
	delete device;
}
