#include "../include/isometricmap.h"
#include "../lib/rapidxml.hpp"
#include "../include/image.h"
#include "../include/math.h"
#include "../include/renderer.h"
#include "../include/isometricscene.h"

using namespace rapidxml;

IsometricMap::IsometricMap(const String& filename, uint16 firstColId) : Map(filename,firstColId)
{
  String contenido = String::Read(filename);
  if (contenido != ""){
    xml_document<> doc;
    //NODO MAPA
    doc.parse<0>((char *)contenido.ToCString());
    xml_node<>* map = doc.first_node("map");
    String aux;
    //NODO TILESET
    xml_node<>* tileset = map->first_node("tileset");
    aux = (char *)tileset->first_attribute("firstgid")->value();
    int firstgid = aux.ToInt();
    //layer && next_sibling
    xml_node<>* layer = map->first_node("layer");
    layer = layer->next_sibling("layer");
    xml_node<>* data = layer->first_node("data");
    xml_node<> *tile = data->first_node("tile");
    while (tile != NULL)
    {
      aux = (char *)tile->first_attribute("gid")->value();
      topLayerIds.Add(aux.ToInt() - firstgid);
      tile = tile->next_sibling("tile");
    }
    int32 x, y;
    x = GetImage()->GetHandleX() + GetTileWidth();
    y = GetImage()->GetHeight() - GetImage()->GetHandleY() - GetTileHeight();
    GetImage()->SetHandle(x, y);
  }
}

void IsometricMap::GenerateLayerSprites(IsometricScene *scene)
{
  //double screenX, screenY;
  for (uint16 y = 0; y < GetRows(); y++) {
    for (uint16 x = 0; x < GetColumns(); x++) {
      if (GetLayerId(x, y) > -1)
      {
        //se genera sprite
        IsometricSprite *nuevo = scene->CreateSprite(GetImage());
        nuevo->SetCurrentFrame(static_cast<uint16>(GetLayerId(x, y)));
        if (GetLayerId(x, y) >= GetFirstColId()){
          nuevo->SetCollisionTam(GetTileWidth(), GetTileWidth());
          nuevo->SetCollision(Sprite::COLLISION_RECT);
        }
        nuevo->SetPosition(x*GetTileWidth(), y*GetTileHeight(), 0);
      }
    }
  }
}

uint16 IsometricMap::GetTileWidth() const 
{
  return Map::GetTileWidth() / 2;
}

void IsometricMap::Render() const 
{
  double screenX = 0.0;
  double screenY = 0.0;

  for (uint16 y = 0; y < GetRows(); y++) {
    for (uint16 x = 0; x < GetColumns(); x++) {
      if (GetTileId(x, y) >= 0) {
        TransformIsoCoords(x*GetTileWidth(), y*GetTileHeight(), 0, &screenX, &screenY);
        RENDER.DrawImage(GetImage(), screenX, screenY, GetTileId(x, y));
      }
    }
  }
}
