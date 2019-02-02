open Revery;
open Revery.Core;
open Revery.Math;
open Revery.UI;
open Revery.UI.Components;

let getColor = (card: Memory.card) =>
  switch (card.value) {
  | 0 => Colors.orange
  | 1 => Colors.blue
  | 2 => Colors.yellow
  | 3 => Colors.red
  | _ => Colors.white
  };

type state = {
  cards: Memory.t,
  flipCount: int,
  gameOver: bool,
};

let initialState = {
  cards: Memory.generateCards(),
  flipCount: 0,
  gameOver: false,
};

type action =
  | FlipCard(int);

let reducer = (action, state) => {
  switch (action) {
  | FlipCard(idx) =>
    let flipCount = state.flipCount + 1;
    let cards = state.cards |> Memory.flipCard(idx);
    let gameOver = Memory.allVisible(cards);

    {gameOver, flipCount, cards};
  };
};

let component = React.component(__MODULE__);

let make = _children =>
  component(slots => {
    let (state, dispatch, slots: React.Hooks.empty) =
      React.Hooks.reducer(~initialState, reducer, slots);

    let containerStyle =
      Style.[
        position(`Absolute),
        justifyContent(`Center),
        alignItems(`Center),
        bottom(0),
        top(0),
        left(0),
        right(0),
        backgroundColor(Colors.white),
      ];

    let textSyle =
      Style.[
        color(Colors.gray),
        fontFamily("canada1500-rg.ttf"),
        fontSize(24),
      ];

    <View style=containerStyle>
      <Grid>
        ...{
             state.cards
             |> List.mapi((idx, c) =>
                  <Card
                    onClick={_ => dispatch(FlipCard(idx))}
                    color={c |> getColor}
                    visible={c.visible}
                  />
                )
           }
      </Grid>
      <Text
        style=textSyle
        text={
          state.gameOver ?
            "Yay, well done" :
            Printf.sprintf("Number of guesses: %d", state.flipCount)
        }
      />
    </View>;
  });

let createElement = (~children, ()) => React.element(make(children));