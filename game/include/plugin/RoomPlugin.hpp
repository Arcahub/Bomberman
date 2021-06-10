#ifndef BC232CC2_8E14_4287_8689_95E97FC42039
#define BC232CC2_8E14_4287_8689_95E97FC42039

#include "ige.hpp"
#include "room/RoomClient.hpp"
#include "room/RoomPlayer.hpp"
#include "room/RoomServer.hpp"

class RoomPlugin : public ige::core::App::Plugin {
public:
    void plug(ige::core::App::Builder&) const override;
};
#endif /* BC232CC2_8E14_4287_8689_95E97FC42039 */
