// Serializar.h
//
//              Metodos sobrecargados de los
//              operadores << y >> 
//              para cargar/salvar la partida
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _SERIALIZAR_H
#define _SERIALIZAR_H

#include "iostream"
#include "EntidadJuego.h"
#include "Objeto.h"
#include "Puerta.h"
#include "Sprite.h"
#include "Personaje.h"
#include "Guillermo.h"
#include "Adso.h"
#include "Malaquias.h"
#include "Abad.h"
#include "Berengario.h"
#include "Severino.h"
#include "Jorge.h"
#include "Bernardo.h"
#include "Logica.h"

namespace Abadia {

std::ostream& operator<< (
	std::ostream& out,
	const PosicionJuego* const pos );

std::istream& operator>> (
	std::istream& in,
	PosicionJuego* const pos );

std::ostream& operator<< (
	std::ostream& out,
	const Objeto* const obj );

std::istream& operator>> (
	std::istream& in,
	Objeto* const obj );

std::ostream& operator<< (
	std::ostream& out,
	const Puerta* const puerta );

std::istream& operator>> (
	std::istream& in,
	Puerta* const puerta );

std::ostream& operator<< (
	std::ostream& out,
	const Sprite* const sprite );

std::istream& operator>> (
	std::istream& in,
	Sprite* const sprite );

std::ostream& operator<< (
	std::ostream& out,
	const Personaje* const pers );

std::istream& operator>> (
	std::istream& in,
	Personaje* const pers );

std::ostream& operator<< (
	std::ostream& out,
	const Guillermo* const guillermo );

std::istream& operator>> (
	std::istream& in,
	Guillermo* const guillermo );

std::ostream& operator<< (
	std::ostream& out,
	const PersonajeConIA* const persIA );

std::istream& operator>> (
	std::istream& in,
	PersonajeConIA* const persIA );

std::istream& operator>> (
	std::istream& in,
	Adso* const adso );

std::ostream& operator<< (
	std::ostream& out,
	const Adso* const adso );

std::ostream& operator<< (
	std::ostream& out,
	const Malaquias* const malaquias );

std::istream& operator>> (
	std::istream& in,
	Malaquias* const malaquias );

std::ostream& operator<< (
	std::ostream& out,
	const Abad* const abad );

std::istream& operator>> (
	std::istream& in,
	Abad* const abad );

std::ostream& operator<< (
	std::ostream& out,
	const Berengario* const berengario );

std::istream& operator>> (
	std::istream& in,
	Berengario* const berengario );

std::ostream& operator<< (
	std::ostream& out,
	const Severino* const severino );

std::istream& operator>> (
	std::istream& in,
	Severino* const severino );

std::ostream& operator<< (
	std::ostream& out,
	const Jorge* const jorge );

std::istream& operator>> (
	std::istream& in,
	Jorge* const jorge );

std::ostream& operator<< (
	std::ostream& out,
	const Bernardo* const bernardo );

std::istream& operator>> (
	std::istream& in,
	Bernardo* const bernardo );

std::ostream& operator<< (
	std::ostream& out,
	const Logica* const logica);

std::istream& operator>> (
	std::istream& in,
	Logica* const logica);

}; // namespace Abadia

#endif // _SERIALIZAR_H
