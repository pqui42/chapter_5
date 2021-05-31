# chapter_5
## Rvalue Refernces, Move Semantics, and Perfect Forwarding
### Item 23: Understand std::move and std::forward
#### Things to Remember
- std::move performs an unconditional cast to an rvalue. In and of itself, it dosen't move anything.
- std::forward cast its arguments to an rvalue only if that argument is bound to an rvalue.
- Neither std::move nor std::forward do anything at runtime.
- move request on const objects are treated as copy request.
