#include "UI/Internal/TextureID.h"

namespace UI::Widgets {

    class Image {
    public:
        /**
		* Constructor
		* @param p_textureID
		* @parma p_size
		*/
		Image(uint32_t p_textureID, const OvMaths::FVector2& p_size);

    public:
		Internal::TextureID textureID;
		//OvMaths::FVector2 size;
    };

}