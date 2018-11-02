﻿#include "PlayerRunJumpState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpThrow.h"
#include "PlayerJumpingState.h"
#include "PlayerClimbState.h"
#include "PlayerJumpPole.h"
#include "PlayerStandHori.h"
#include "../../GameDefines/GameDefine.h"

PlayerRunJumpState::PlayerRunJumpState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

    acceleratorY =20.0f;
    acceleratorX = 0.0f;

	
	
	this->mPlayerData->player->AddVy(100);
    noPressed = false;
}


PlayerRunJumpState::~PlayerRunJumpState()
{

}

void PlayerRunJumpState::Update(float dt)
{
    this->mPlayerData->player->AddVy(acceleratorY);   
	/*if (mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 5) 
		mPlayerData->player->GetCurrentAnimation()->SetCurrentFrame(4);*/
    /*if (mPlayerData->player->GetVy() >= 0)
    {
		mPlayerData->player->GetCurrentAnimation()->Reset();
        mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
        return;
    }*/
	if (mPlayerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
	{
		mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	}

}

void PlayerRunJumpState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VkKeyScan('x')])
	{

	}
	else if (keys[VkKeyScan('z')])
	{
		this->mPlayerData->player->SetState(new PlayerJumpThrow(this->mPlayerData));
	}else
    if (keys[VK_RIGHT] )
    {

        mPlayerData->player->SetReverse(false);
		isLeftOrRightKeyPressed = true;
        //di chuyen sang phai
        if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
        {
            //this->mPlayerData->player->AddVx(acceleratorX);
			this->mPlayerData->player->SetVx(150);
            if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
            } 
        }

        noPressed = false;
    }
    else if (keys[VK_LEFT] )
    {
        mPlayerData->player->SetReverse(true);
		isLeftOrRightKeyPressed = true;
        //di chuyen sang trai
        if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
        {
            //this->mPlayerData->player->AddVx(-acceleratorX);
			this->mPlayerData->player->SetVx(-150);
            if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }

        noPressed = false;
    }
	
    else
    {
        noPressed = true;
		isLeftOrRightKeyPressed = false;
    }
	
}

PlayerState::StateName PlayerRunJumpState::GetState()
{
    return PlayerState::RunJump;
}
void PlayerRunJumpState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//if (impactor->Tag == Entity::Bung || impactor->Tag == Entity::stair || impactor->Tag == Entity::stair1 || impactor->Tag == Entity::stair2) return;
	if (impactor->Tag == Entity::stair && this->mPlayerData->player->GetVy()>0)
	{
		if (mPlayerData->player->GetPosition().x < 2000) {
			D3DXVECTOR2 A = /*impactor->GetPosition();*/D3DXVECTOR2(1144, 625);
			D3DXVECTOR2 B =/* D3DXVECTOR2(A.x + impactor->GetWidth() / 2, A.y - impactor->GetHeight() / 2);*/D3DXVECTOR2(1394, 567);
			D3DXVECTOR2 vtcp = D3DXVECTOR2(B.x - A.x, B.y - A.y);
			D3DXVECTOR2 vtpt = D3DXVECTOR2(vtcp.y, -vtcp.x);

			float y = (-vtpt.x*(mPlayerData->player->GetPosition().x - A.x)) / vtpt.y + A.y;

			if (y - mPlayerData->player->GetPosition().y <= 30)
			{
				if (mPlayerData->player->GetPosition().x > 1394) {
					mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, mPlayerData->player->GetPosition().y);
					mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
				}
				else {
					mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, y);
					mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
				}
			}
			return;
		}
		else if (mPlayerData->player->GetPosition().x < 4000 && mPlayerData->player->GetPosition().x >3700)
		{
			D3DXVECTOR2 A = D3DXVECTOR2(3800, 485);
			D3DXVECTOR2 B = D3DXVECTOR2(3955, 440);
			//D3DXVECTOR2 A = impactor->GetPosition();
			//D3DXVECTOR2 B = D3DXVECTOR2(A.x + impactor->GetWidth() / 2, A.y - impactor->GetHeight() / 2);
			//D3DXVECTOR2 A = /*impactor->GetPosition();*/D3DXVECTOR2(1144, 6);
			D3DXVECTOR2 vtcp = D3DXVECTOR2(B.x - A.x, B.y - A.y);
			D3DXVECTOR2 vtpt = D3DXVECTOR2(vtcp.y, -vtcp.x);

			float y = (-vtpt.x*(mPlayerData->player->GetPosition().x - A.x)) / vtpt.y + A.y;
			if (y - mPlayerData->player->GetPosition().y <= 30)
			{
				if (mPlayerData->player->GetPosition().x > 3955) {
					mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, mPlayerData->player->GetPosition().y);
					mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
				}
				else {
					mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, y);
					mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
				}
			}
			return;
		}
		else
		{
			D3DXVECTOR2 A = D3DXVECTOR2(4380, 648);
			D3DXVECTOR2 B = D3DXVECTOR2(4475, 625);
			D3DXVECTOR2 vtcp = D3DXVECTOR2(B.x - A.x, B.y - A.y);
			D3DXVECTOR2 vtpt = D3DXVECTOR2(vtcp.y, -vtcp.x);


			float y = (-vtpt.x*(mPlayerData->player->GetPosition().x - A.x)) / vtpt.y + A.y;
			if (y - mPlayerData->player->GetPosition().y <= 30)
			{
				if (mPlayerData->player->GetPosition().x > 4560) {
					mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, mPlayerData->player->GetPosition().y);
					mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
				}
				else {
					mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, y);
					mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
				}
			}
			return;
		}
	}
	if (impactor->Tag == Entity::Rope)
	{
		mPlayerData->player->SetPosition(impactor->GetPosition().x, mPlayerData->player->GetPosition().y);
		mPlayerData->player->SetVx(0);
		mPlayerData->player->SetVy(0);
		//mPlayerData->player->allowJump = true;
		mPlayerData->player->SetState(new PlayerClimbState(this->mPlayerData));


		return;
	}
	if (impactor->Tag == Entity::StringHori && (side == Entity::Top || side == Entity::TopRight || side == Entity::TopLeft))
	{
		mPlayerData->player->SetReverse(mPlayerData->player->GetReverse());
		//mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x,impactor->GetPosition().y);
		mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, mPlayerData->player->GetPosition().y + 55);

		mPlayerData->player->SetVy(0);
		mPlayerData->player->SetState(new PlayerStandHori(this->mPlayerData));
		return;
	}
	if (impactor->Tag == Entity::AppleObject)
		return;


	switch (side)
	{
	case Entity::Left:
	{
		if (impactor->Tag != Entity::LandWood)
		{
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->mPlayerData->player->SetVx(0);
		}
		break;
	}

	case Entity::Right:
	{
		if (impactor->Tag != Entity::LandWood)
		{
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->mPlayerData->player->SetVx(0);
		}
		break;
	}

	case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
	{
		break;
	}

	case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
	{
		if (impactor->Tag == Entity::flagPole)
		{

			mPlayerData->player->SetState(new PlayerJumpPole(this->mPlayerData));
			return;
		}
		if (impactor->Tag == Entity::Camel)
		{
			this->mPlayerData->player->SetState(new PlayerJumpingState(this->mPlayerData));
			return;
		}
		if (impactor->Tag == Entity::StringHori)
		{
			return;
		}
		//if (data.RegionCollision.right - data.RegionCollision.left >= 16.0f)
		//{

			//this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top)); //Code cho player đứng trên vật thể
			//RECT r = this->mPlayerData->player->GetBound();
			//if (isLeftOrRightKeyPressed)
			//{
			//	mPlayerData->player->GetCurrentAnimation()->Reset();
			//	this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
			//}
			//else
			//{
			//	mPlayerData->player->GetCurrentAnimation()->Reset();
			//	this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			//}
		//}
		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		if (data.RegionCollision.right - data.RegionCollision.left >= 16.0f && this->mPlayerData->player->GetVy()>0)
		{
			mPlayerData->player->GetCurrentAnimation()->Reset();
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		}
		return;


	default:
		break;
	}
	}
}