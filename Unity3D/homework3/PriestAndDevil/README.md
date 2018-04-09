# Priests and Devils

## 修改部分

- 增加了DnPseedAction, ActionManager, DnPActionCompCallback
- 简化了状态，变为4个状态： Moving, Idle, WIN, LOSE
- 加入变量boat_side记录boat的位置
- Moving 状态下禁止用户输入
