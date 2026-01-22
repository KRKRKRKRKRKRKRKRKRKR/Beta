#include "Scene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "CreditScene.h"
#include "RankingScene.h"

SceneManager::SceneManager()
{
	currentType_ = SceneType::Title;
	currentScene_ = new TitleScene(this);
}

SceneManager::~SceneManager()
{
	if (currentScene_)
	{
		delete currentScene_;
	}
}

void SceneManager::ChangeScene(SceneType newType)
{
	if (inTransition_) return;

	if (newType == currentType_) return;

	StartTransition(newType);
}

//Work in progress
void SceneManager::StartTransition(SceneType to)
{
    inTransition_ = true;
    switchingDone_ = false;
    nextType_ = to;
    phase_ = 0;

    // Phase 0: vertical close (1 -> 0) over 30 frames
    vertEasing_.Init(1.0f, 0.0f, transitionTotalFrame_, EasingType::EASING_EASE_IN_OUT_QUAD);
    vertEasing_.Start();

    // Phase 1: horizontal close (1 -> 0) over 30 frames - will start later
    horizEasing_.Init(1.0f, 0.0f, transitionTotalFrame_, EasingType::EASING_EASE_IN_OUT_QUAD);
    // do NOT call horizEasing_.Start() here
}

void SceneManager::UpdateTransition()
{
    switch (phase_)
    {
    case 0: // vertical close (full screen -> horizontal line)
        vertEasing_.Update();
        // while closing vertically, horizontal scale stays at 1
        horizEasing_.easingRate = 1.0f;

        if (!vertEasing_.isMove) {
            // start horizontal close
            phase_ = 1;
            horizEasing_.Start();
        }
        break;

    case 1: // horizontal close (line -> dot)
        horizEasing_.Update();
        // while closing horizontally, vertical is already 0
        vertEasing_.easingRate = 0.0f;

        if (!horizEasing_.isMove && !switchingDone_) {
            // fully closed -> switch scenes here
            switchingDone_ = true;

            delete currentScene_;
            currentScene_ = nullptr;
            currentType_ = nextType_;

            switch (nextType_) {
            case SceneType::Title:   currentScene_ = new TitleScene(this);   break;
            case SceneType::Play:    currentScene_ = new PlayScene(this);    break;
            case SceneType::Credit:  currentScene_ = new CreditScene(this);  break;
            case SceneType::Ranking: currentScene_ = new RankingScene(this); break;
            }

            // prepare opening phases
            phase_ = 2;

            // horizontal open: 0 -> 1
            horizEasing_.Init(0.0f, 1.0f, transitionTotalFrame_, EasingType::EASING_EASE_IN_OUT_QUAD);
            horizEasing_.Start();

            // keep vertical at 0 at the beginning of the open
            vertEasing_.easingRate = 0.0f;
        }
        break;

    case 2: // horizontal open (dot -> line)
        horizEasing_.Update();
        vertEasing_.easingRate = 0.0f; // still a line

        if (!horizEasing_.isMove) {
            // start vertical open
            phase_ = 3;
            vertEasing_.Init(0.0f, 1.0f, transitionTotalFrame_, EasingType::EASING_EASE_IN_OUT_QUAD);
            vertEasing_.Start();
        }
        break;

    case 3: // vertical open (line -> full screen)
        vertEasing_.Update();
        horizEasing_.easingRate = 1.0f; // full width

        if (!vertEasing_.isMove) {
            // transition finished
            inTransition_ = false;
        }
        break;
    }
}

void SceneManager::DrawCurrentScene()
{
    Novice::ScreenPrintf(0, 0, "inTransition=%d", inTransition_ ? 1 : 0);

    const int screenW = 1280;
    const int screenH = 720;

    if (!inTransition_) {
        // Normal: just draw the scene
        if (currentScene_) {
            currentScene_->Draw();
        }
    }
    else {
        // During transition: white background instead of scene content
        Novice::DrawBox(0, 0, screenW, screenH, 0.0f, WHITE, kFillModeSolid);
    }

    // TV overlay effect on top (uses white as base)
    if (inTransition_) {
        DrawTransitionOverlay();
    }
}

void SceneManager::UpdateCurrentScene(char* keys, char* preKeys)
{
    if (!inTransition_) {
        // Normal update
        if (currentScene_) {
            currentScene_->Update(keys, preKeys);
        }
    }
    else {
        // During transition we freeze the scenes
        // (no Update on current or next scene)
    }

    if (inTransition_) {
        UpdateTransition();
    }
}

void SceneManager::DrawTransitionOverlay()
{
    // Debug
    Novice::ScreenPrintf(0, 20, "Transition ON phase=%d", phase_);
    Novice::ScreenPrintf(0, 40, "w=%.2f h=%.2f",
        horizEasing_.easingRate, vertEasing_.easingRate);

    const int screenW = 1280;
    const int screenH = 720;
    const int centerX = screenW / 2;
    const int centerY = screenH / 2;

    unsigned int color = 0x222222FF; // or DARKGRAY while tuning

    // Copy scales locally and clamp
    float wScale = horizEasing_.easingRate;
    float hScale = vertEasing_.easingRate;
    if (wScale < 0.0f) wScale = 0.0f;
    if (wScale > 1.0f) wScale = 1.0f;
    if (hScale < 0.0f) hScale = 0.0f;
    if (hScale > 1.0f) hScale = 1.0f;

    // Phase 0 & 3: vertical squash / expand (top/bottom only)
    if (phase_ == 0 || phase_ == 3)
    {
        // hScale: 1.0 = full screen, 0.0 = horizontal line
        int visibleH = static_cast<int>(screenH * hScale);
        int top = centerY - visibleH / 2;
        int bottom = centerY + visibleH / 2;

        if (visibleH <= 0) {
            // Screen collapsed to a line: cover entire screen (just in case)
            Novice::DrawBox(0, 0, screenW, screenH, 0.0f, color, kFillModeSolid);
            return;
        }

        // TOP bar
        if (top > 0) {
            Novice::DrawBox(0, 0, screenW, top, 0.0f, color, kFillModeSolid);
        }

        // BOTTOM bar
        if (screenH - bottom > 0) {
            Novice::DrawBox(0, bottom, screenW, screenH - bottom, 0.0f, color, kFillModeSolid);
        }
    }
    // Phase 1 & 2: horizontal pinch / expand (left/right only)
    else if (phase_ == 1 || phase_ == 2)
    {
        int lineThickness = 4;
        int top = centerY - lineThickness / 2;
        int bottom = centerY + lineThickness / 2;

        int visibleW = static_cast<int>(screenW * wScale);
        int left = centerX - visibleW / 2;
        int right = centerX + visibleW / 2;

        if (visibleW <= 0) {
            Novice::DrawBox(0, 0, screenW, screenH, 0.0f, color, kFillModeSolid);
            return;
        }

        // LEFT / RIGHT bars
        if (left > 0) {
            Novice::DrawBox(0, top, left, lineThickness, 0.0f, color, kFillModeSolid);
        }
        if (screenW - right > 0) {
            Novice::DrawBox(right, top, screenW - right, lineThickness, 0.0f, color, kFillModeSolid);
        }

        // Black above and below
        Novice::DrawBox(0, 0, screenW, top, 0.0f, color, kFillModeSolid);
        Novice::DrawBox(0, bottom, screenW, screenH - bottom, 0.0f, color, kFillModeSolid);

        // ---- circle flash ----
        float t = 1.0f - wScale;          // 0..1 as bars close
        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;

        float alphaT = t * (1.0f - t) * 4.0f;  // 0 -> 1 -> 0

        // brightness levels example
        unsigned int circleColor;
        if (alphaT < 0.3f) {
            circleColor = 0;            // invisible
        }
        else if (alphaT < 0.6f) {
            circleColor = 0xD3D3D3FF;    // medium
        }
        else {
            circleColor = WHITE;        // bright flash
        }

        if (circleColor != 0) {
            float minRadius = 10.0f;
            float maxRadius = 80.0f;
            float radius = minRadius + (maxRadius - minRadius) * t;

            Novice::DrawEllipse(
                centerX, centerY,
                (int)radius, (int)radius,
                0.0f,
                circleColor,
                kFillModeSolid
            );
        }
    }
}