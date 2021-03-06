#include "../include/affector.h"
#include "../include/math.h"
#include "../include/particle.h"

Affector::Affector(bool color, bool velX, bool velY, bool velAng)
{
  modificarColor = color;
  modificarVelX = velX;
  modificarVelY = velY;
  modificarVelAng = velAng;
  origAncho = origAlto = finAlto = finAncho = 0;
  minr = ming = minb = maxr = maxg = maxb = 0;
  minangvel = minvelx = minvely = 0.0;
  maxangvel = maxvelx = maxvely = 0.0;
}

double Affector::getNuevaVelX() const
{
  return (minvelx == 0 && maxvelx == 0) ? 0 : WrapValue(rand(), maxvelx - minvelx) + minvelx;
}
double Affector::getNuevaVelY() const
{
  return (minvely == 0 && maxvely == 0) ? 0 : WrapValue(rand(), maxvelx - minvelx) + minvely;
}
double Affector::getNuevaAngleVel() const
{
  return (minangvel == 0 && maxangvel == 0) ? 0 : WrapValue(rand(), maxangvel - minangvel) + minangvel;
}
uint8 Affector::getNuevoRed() const
{
  if (maxr == 0 && minr == 0)
    return 0;
  return (maxr ==  minr) ? maxr : rand() % (maxr - minr) + minr;
}
uint8 Affector::getNuevoGreen() const
{
  if (maxg == 0 && ming == 0)
    return 0;
  return (maxg == ming) ? maxg : rand() % (maxg - ming) + ming;
}
uint8 Affector::getNuevoBlue() const
{
  if (maxb == 0 && minb == 0)
    return 0;
  return (maxb == minb) ? maxb : rand() % (maxb - minb) + minb;
}

void Affector::Afectar(Particle *particula)
{
  if (particula->GetX() >= origAncho && particula->GetX() <= finAncho)
    if (particula->GetY() >= origAlto && particula->GetY() <= finAlto)
    {
      if (modificarColor)
        particula->SetColor(getNuevoRed(), getNuevoGreen(), getNuevoBlue());
      if (modificarVelX)
        particula->setVelocityX(getNuevaVelX());
      if (modificarVelY)
        particula->setVelocityX(getNuevaVelY());
      if (modificarVelAng)
        particula->setVelocityAng(getNuevaAngleVel());
      particula->Alter();
    }
}