open Revery;
open Revery.Core;
open Revery.Math;
open Revery.UI;
open Revery.UI.Components;

let component = React.component(__MODULE__);

let make = (~onClick, ~col, ~visible) =>
  component((_slots: React.Hooks.empty) => {
    let style =
      Style.[
        position(`Relative),
        width(120),
        height(120),
        margin(30),
        backgroundColor(visible ? col : Colors.white),
        opacity(0.8),
        boxShadow(
          ~xOffset=-9.,
          ~yOffset=-14.,
          ~spreadRadius=14.,
          ~blurRadius=14.,
          ~color=Colors.lightGray,
        ),
      ];

    <Clickable onClick> <View style /> </Clickable>;
  });

let createElement = (~children, ~onClick, ~color as col, ~visible, ()) =>
  React.element(make(~onClick, ~col, ~visible));