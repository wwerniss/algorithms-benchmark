#pragma once

#include "SortingWindow.h"

/**
 * @class IWindowActivityState
 * @brief Interface for the State design pattern applied to SortingWindow.
 * 
 * Encapsulates the varying behaviors and UI availability requirements based entirely
 * on the current state of the application algorithm player.
 */
class IWindowActivityState {
public:
    virtual ~IWindowActivityState() = default;
    
    /** @brief Triggers the Play or Pause action logic and transitions. */
    virtual void handlePlayPause(SortingWindow* window) = 0;
    /** @brief Executes a single algorithmic forward step. */
    virtual void handleStepForward(SortingWindow* window) = 0;
    /** @brief Executes a single algorithmic backward Undo action. */
    virtual void handleStepBackward(SortingWindow* window) = 0;
    /** @brief Begins the algorithmic visualization sequence and data generation. */
    virtual void handleSortStart(SortingWindow* window) = 0;
    /** @brief Cleans up and stops timers when the algorithm finishes. */
    virtual void handleSortEnd(SortingWindow* window) = 0;
    
    /** @brief Updates enablement state of GUI buttons appropriately. */
    virtual void updateUI(SortingWindow* window) = 0;
};

/**
 * @class RunningState
 * @brief Represents the state where the sorting animation is actively playing.
 */
class RunningState : public IWindowActivityState {
public:
    void handlePlayPause(SortingWindow* window) override;
    void handleStepForward(SortingWindow* window) override {} ///< Disabled while playing
    void handleStepBackward(SortingWindow* window) override {} ///< Disabled while playing
    void handleSortStart(SortingWindow* window) override {} ///< Ignored while playing
    void handleSortEnd(SortingWindow* window) override;
    
    void updateUI(SortingWindow* window) override;
};

/**
 * @class PausedState
 * @brief Represents the state where the algorithm has paused mid-execution.
 */
class PausedState : public IWindowActivityState {
public:
    void handlePlayPause(SortingWindow* window) override;
    void handleStepForward(SortingWindow* window) override;
    void handleStepBackward(SortingWindow* window) override;
    void handleSortStart(SortingWindow* window) override;
    void handleSortEnd(SortingWindow* window) override;
    
    void updateUI(SortingWindow* window) override;
};

/**
 * @class IdleState
 * @brief Represents the base state where no algorithm is actively running or paused.
 */
class IdleState : public IWindowActivityState {
public:
    void handlePlayPause(SortingWindow* window) override {} ///< Ignored
    void handleStepForward(SortingWindow* window) override {} ///< Ignored
    void handleStepBackward(SortingWindow* window) override {} ///< Ignored
    void handleSortStart(SortingWindow* window) override;
    void handleSortEnd(SortingWindow* window) override {} ///< Ignored
    
    void updateUI(SortingWindow* window) override;
};
