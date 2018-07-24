#pragma once

#ifndef _UGP_LIGHT_H_
#define _UGP_LIGHT_H_

struct stLight //�����ƹ���� �������������D3D����
{
	stLight()
	{
		type = 0; //�ƹ�����
		posx =0,posy =0,posz =0; //λ��
		dirx =0,diry =0,dirz =0; //����
		ambientR =ambientG=ambientB=ambientA=1; //������ǿ��
		diffuseR =diffuseG=diffuseB=diffuseA=1; //������ǿ��
		specularR=specularG=specularB=specularA=0; //�߹�ǿ��
		range = 0; //�����÷�Χ
		falloff = 0; //��ǿ��˥��
		attenuation0 = 0; //���ھ��������ȵĸı䷽ʽ
		attenuation1 = 0;
		attenuation2 = 0;
		theta = 0; //�۹���ڲ�׵�廡�Ƚ�
		phi = 0;  //�۹���ⲿ׵�廡�Ƚ�
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