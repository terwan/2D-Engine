#include "World1.h"
#include "Player.h"
#include "AI.h"
#include "PhysicSystem.h"
#include "RenderSystem.h"

uint16 spotId, obsId;

using namespace ooe;

void World1::init()
{
	tag_ = "test world";
	gfx.star().create();

	gfx.load("resources/spot.jpg", spotId);
	gfx.load("resources/obstacle.jpg", obsId);

#pragma region Rapidly-Exploring Random Tree
	//region holding All setup code for RRT algorithm
	//RRT algorithm found in AISystem->RRT

	//Note: Some parameters may need changing for different maps
	//eg: x_obs needs changing from 'T' to '@' for some of the maps to render appropriately
	std::string map_name = "arena";
	char x_free = '.';
	char x_obs = 'T';
	size_t k = 200;
	size_t dt = 1;


	FileHandling fh;
	std::string directory = "resources/maps/"+map_name+"/";
	auto height = (int)parse(fh.ReadFF(directory+map_name+".map", "height"));
	auto width = (int)parse(fh.ReadFF(directory+map_name+".map", "width"));
	auto map = fh.ReadToEnd(directory+map_name+".map", "map");
	std::uniform_int_distribution<int> rand_x(0, width);
	std::uniform_int_distribution<int> rand_y(0, height);
	app.rrt().init(Map(map, width, height, x_free, x_obs));

	vec2 x_init;
	x_init = vec2(rand_x(min_rand_), rand_y(min_rand_));

#pragma endregion 


#pragma region quick setup of some test entities

	uint16 playerid, enemyid;
	gfx.load("resources/playerSprite.tga", playerid);
	gfx.load("resources/alphaThing.tga", enemyid);

	auto player = new Entity("player");
	auto pos = player->componentManager().getComponent<Transform>()->translation;
	pos = vec2(gfx.width()/2, gfx.height()/2);
	player->componentManager().addComponent<User>();
	player->componentManager().addComponent<Model>()->sprite_id = playerid;
	player->componentManager().addComponent<CollisionBox>()->collision_box = Rectangle(pos.i, pos.j, gfx.spriteDimensions(playerid).width, gfx.spriteDimensions(playerid).height);

	auto gamepad = player->componentManager().getComponent<User>();
	gamepad->boundary = Rectangle(0, 0, gfx.width(), gfx.height()) - gfx.spriteDimensions(playerid);
	gamepad->sensitivity = 30;
	gamepad->keyboard = app.input().KeyboardData();
	gamepad->gamepad = app.input().GamepadData();


	auto enemy = new Entity("enemy"); 
	pos = enemy->componentManager().getComponent<Transform>()->translation;
	pos = vec2(30, 40);
	enemy->componentManager().addComponent<Model>()->sprite_id = enemyid;
	enemy->componentManager().addComponent<CollisionBox>()->collision_box = Rectangle(pos.i, pos.j, gfx.spriteDimensions(enemyid).width, gfx.spriteDimensions(enemyid).height);
	enemy->componentManager().addComponent<Logic>()->tree = *app.rrt().generateRRT(x_init, k, dt);
	enemy->componentManager().getComponent<Logic>()->speed = 1;
	
#pragma endregion
}

void World1::update()
{
	//clear screen to a colour
	gfx.clearColour(HAPI_TColour(200,200,200));
	gfx.star().GenerateStars(gfx.width(), gfx.height());

	auto enemy = engine.object("enemy");
	auto player = engine.object("player");

	auto logic = enemy->componentManager().getComponent<Logic>();
	logic->target = player->componentManager().getComponent<Transform>()->translation;

	//Draw order means nodes on tree will lie ontop of map so it's easier to see whether nodes are within x_obs
	app.rrt().renderMap(obsId);
	app.rrt().drawTree(spotId);
}
