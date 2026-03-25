#pragma once

namespace core {
namespace patterns {

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

} // namespace patterns
} // namespace core
