#pragma once

#ifndef _UGP_LIGHT_H_
#define _UGP_LIGHT_H_

struct stLight //创建灯光对象 把这个对象分配给D3D对象
{
	stLight()
	{
		type = 0; //灯光类型
		posx =0,posy =0,posz =0; //位置
		dirx =0,diry =0,dirz =0; //方向
		ambientR =ambientG=ambientB=ambientA=1; //环境光强度
		diffuseR =diffuseG=diffuseB=diffuseA=1; //漫反射强度
		specularR=specularG=specularB=specularA=0; //高光强度
		range = 0; //光作用范围
		falloff = 0; //光强度衰减
		attenuation0 = 0; //光在距离上亮度的改变方式
		attenuation1 = 0;
		attenuation2 = 0;
		theta = 0; //聚光灯内部椎体弧度角
		phi = 0;  //聚光灯外部椎体弧度角
	}

	int type;
	float posx,posy,posz;
	float dirx,diry,dirz;
	float ambientR,ambientG,ambientB,ambientA;
	float diffuseR, diffuseG, diffuseB, diffuseA;
	float specularR,specularG,specularB,specularA;
	float range;
	float falloff ;
	float attenuation0 ;
	float attenuation1 ;
	float attenuation2 ;
	float theta ;
	float phi ;
};

#endif