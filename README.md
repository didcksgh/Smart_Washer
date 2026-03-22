# SmartWash
Embedded Washing Machine Control Simulation
세탁기 제어 로직 기반 임베디드 시스템 시뮬레이션

## Overview | 프로젝트 개요

SmartWash is a C++-based embedded system simulation that models the control logic of an automatic washing machine using a deterministic state-machine architecture.

SmartWash는 자동 세탁기의 제어 로직을 상태 머신 기반으로 모델링한 C++ 임베디드 시스템 시뮬레이션 프로젝트입니다.

The system simulates real-time interaction between sensors, actuators, and control logic under constrained execution conditions.

센서, 액추에이터, 제어 로직 간의 실시간 상호작용을 제한된 실행 환경에서 재현하도록 설계되었습니다.

This project focuses on embedded control design, real-time state modeling, hardware abstraction, and fault-aware system behavior.

본 프로젝트는 임베디드 제어 설계, 실시간 상태 모델링, 하드웨어 추상화, 오류 대응 시스템 설계 역량을 중심으로 구현되었습니다.


## System Architecture | 시스템 구조

The system is organized into three core layers:

본 시스템은 세 가지 핵심 계층 구조로 구성됩니다.


1. Control Layer | 제어 계층

•Deterministic finite state machine 기반 세탁 사이클 제어

•Washing cycle state management:

Idle → Filling → Washing → Rinsing → Spinning → Error

•상태 전이는 다음 조건에 의해 발생:

   •Sensor input (수위, 도어 상태)

   •Timing constraints (시간 제한)

   •Fault detection (오류 상태)

•Safety constraints enforced:

   •Fill timeout detection

   •Drain timeout detection

   •Door safety interrupt

   •Fault-driven recovery logic

Runtime state definitions include:

•WasherState

•RinsePhase

•FaultCode

이를 통해 런타임 시스템 동작 상태를 명확하게 모델링했습니다.


2. Sensor Abstraction Layer | 센서 추상화 계층

Simulates hardware sensor inputs:

•Door state

•Water level

•Temperature

센서 모듈은 다음 기능을 지원합니다:

•Runtime sensor update interface

•Manual test injection interface

이를 통해 실시간 제어 로직의 결정론적 테스트 환경을 구축했습니다.


3. Actuator Control Layer | 액추에이터 제어 계층

Models physical device outputs:

•Water valve control

•Heater control

•Drain pump control

•Motor speed control

Actuator 상태는 현재 제어 상태에 따라 지속적으로 갱신됩니다.


## State Machine Design | 상태 머신 설계

The washing cycle is governed by a hierarchical state machine.

세탁 사이클은 계층형 상태 머신 구조로 설계되었습니다.

Example flow:

Idle → Filling → Washing → Rinsing → Spinning → Idle

Rinsing phase includes sub-states:

Drain → Fill → Agitate

Controller guarantees:

•Deterministic execution flow

•Fault-aware recovery

•Loop safety via bounded iteration guard

이를 통해 무한 루프 및 비정상 상태 진행을 방지하는 안정적 제어 구조를 구현했습니다.


## Wash Mode Configuration | 세탁 모드 구성

Supports multiple washing modes:

•Normal

•Quick

•Heavy

각 모드는 다음 구성 요소를 포함합니다:

•Target water level

•Cycle duration

•Motor speed profile

•Heater usage policy

•Rinse iteration count

This abstraction enables extensible washing logic configuration.


## Logging System | 로깅 시스템

Dedicated diagnostic logging module records:

•State transitions

•Mode selections

•Full actuator state snapshot

이는 실제 가전 임베디드 시스템에서 사용되는 진단 텔레메트리 구조를 모사합니다.


## Engineering Focus | 핵심 기술 역량

This project demonstrates:

•Deterministic embedded control architecture design

•Real-time state machine implementation

•Hardware abstraction via modular interfaces

•Failure-aware control flow design

•Structured fault recovery mechanism

•Configurable embedded system behavior

→ 임베디드 제어 아키텍처 설계 능력
→ 실시간 상태 머신 구현 경험
→ 모듈 기반 하드웨어 추상화 설계
→ 오류 대응 제어 로직 설계 경험
→ 안정성 중심 시스템 설계 역량 확보


## How to Run | 실행 방법

Compile with standard C++ compiler:

g++ src/*.cpp -o washer_app
./washer_app


## Future Improvements | 향후 개선 방향

Planned extensions include:

•Load-weight adaptive washing logic

•Energy efficiency optimization model

•Sensor noise simulation

•Interrupt-driven scheduling

•RTOS-style task separation

→ 세탁량 기반 적응형 제어 로직
→ 에너지 최적화 모델링
→ 센서 노이즈 시뮬레이션
→ 인터럽트 기반 스케줄링
→ RTOS 스타일 태스크 구조 도입

Author
Chanho Yang