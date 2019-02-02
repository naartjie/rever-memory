open Revery;
open Revery.Core;
open Revery.Math;
open Revery.UI;
open Revery.UI.Components;

let split = (list, n) => {
  let rec aux = (i, acc) =>
    fun
    | [] => (List.rev(acc), [])
    | [h, ...t] as l =>
      if (i == 0) {
        (List.rev(acc), l);
      } else {
        aux(i - 1, [h, ...acc], t);
      };
  aux(n, [], list);
};

let component = React.component(__MODULE__);

let make = (~children) =>
  component((_slots: React.Hooks.empty) => {
    let style =
      Style.[
        flexDirection(`Row),
        justifyContent(`Center),
        alignItems(`Center),
      ];
    let (row1, row2) = split(children, 4);

    <View> <View style> ...row1 </View> <View style> ...row2 </View> </View>;
  });

let createElement = (~children, ()) => React.element(make(~children));