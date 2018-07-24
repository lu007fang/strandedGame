#pragma once

#ifndef _UGP_MATERIAL_H_
#define _UGP_MATERIAL_H_

struct stMaterial //创建材质对象 把这个对象分配给D3D对象
{
	stMaterial()
	{
		emissiveR=emissiveG=emissiveB=emissiveA=0;
		ambientR =ambientG=ambientB=ambientA=1;
		diffuseR =diffuseG=diffuseB=diffuseA=1;
		specularR=specularG=specularB=specularA=0;
		power = 0;
	}

	int type;
	float emissiveR,emissiveG,emissiveB,emissiveA;
	float ambientR,ambientG,ambientB,ambientA;
	float diffuseR, diffuseG, diffuseB, diffuseA;
	float specularR,specularG,specularB,specularA;
	float power;



};


#endif