
namespace UI::Internal {

    /**
	* Simple union necessary for imgui textureID
	*/
    union TextureID
	{
		uint32_t id;
		void* raw;
	};
}