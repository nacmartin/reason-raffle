type action =
  | PersonSelected(int)
  | PrizeSelected
  | PersonWins(int);

type phase =
  | Waiting
  | InRaffle
  | ShowNextPrize
  | ShowWinner;

type state = {
  persons: list(Person.person),
  prizes: list(Prize.prize),
  numberSelected: option(int),
  prizeInRaffle: option(int),
  alreadySelected: list(int),
  phase
};

let component = ReasonReact.reducerComponent("App");

let fibonacci = (prev: int, prev_prev: int) => prev + prev_prev;

let raffle = self => {
  let rec loop = (state, time, prev_time) => {
    let tmp = ref(state);
    let options =
      List.filter(
        (person: Person.person) =>
          ! List.mem(person.id, state.alreadySelected),
        self.ReasonReact.state.persons
      );
    let chosen = List.nth(options, Random.int(List.length(options)));
    let next_time = fibonacci(time, prev_time);
    let finished = time > 60;
    finished ?
      self.ReasonReact.send(PersonWins(chosen.id)) :
      self.ReasonReact.send(PersonSelected(chosen.id));
    switch finished {
    | false =>
      Window.setTimeout(() => loop(tmp^, next_time, time), next_time * 20)
      |> ignore
    | true => ()
    };
  };
  loop(self.ReasonReact.state, 1, 0);
};

let handleClick = (_event, self) =>
  switch self.ReasonReact.state.phase {
  | InRaffle => ()
  | Waiting => self.ReasonReact.send(PrizeSelected)
  | ShowNextPrize => raffle(self)
  | ShowWinner => self.ReasonReact.send(PrizeSelected)
  };

let isSelected = (numberSelected: option(int), id: int) =>
  switch numberSelected {
  | None => false
  | Some(a) when a === id => true
  | _ => false
  };

let nextPrize = (prizeIdx: option(int)) =>
  switch prizeIdx {
  | None => Some(0)
  | Some(a) => Some(a + 1)
  };

let make = _children => {
  ...component,
  initialState: () => {
    persons: [
      {fullName: "John", id: 0},
      {fullName: "Por", id: 1},
      {fullName: "Nol", id: 2},
      {fullName: "nu", id: 3},
      {fullName: "Allo", id: 4},
      {fullName: "Op", id: 5},
      {fullName: "Pate", id: 6},
      {fullName: "Sette", id: 7}
    ],
    prizes: [
      {name: "A subscription", assignedTo: None},
      {name: "Some other thing", assignedTo: None},
      {name: "more stuff", assignedTo: None}
    ],
    prizeInRaffle: None,
    numberSelected: None,
    phase: Waiting,
    alreadySelected: []
  },
  reducer: (action, state) =>
    switch action {
    | PersonSelected(id) =>
      ReasonReact.Update({...state, numberSelected: Some(id), phase: InRaffle})
    | PersonWins(id) =>
      ReasonReact.Update({
        ...state,
        numberSelected: None,
        phase: ShowWinner,
        alreadySelected: [id, ...state.alreadySelected]
      })
    | PrizeSelected =>
      ReasonReact.Update({
        ...state,
        prizeInRaffle: nextPrize(state.prizeInRaffle),
        phase: ShowNextPrize
      })
    },
  render: self => {
    let {
      numberSelected,
      phase,
      persons,
      alreadySelected,
      prizes,
      prizeInRaffle
    } =
      self.state;
    <div>
      <button onClick=(self.handle(handleClick))>
        (ReasonReact.stringToElement("go"))
      </button>
      (
        ReasonReact.arrayToElement(
          Array.of_list(
            List.map(
              (person: Person.person) =>
                <Person
                  person
                  selected=(isSelected(numberSelected, person.id))
                  inRaffle=(phase === InRaffle)
                  key=person.fullName
                  alreadySelected=(
                    List.exists(id => id === person.id, alreadySelected)
                  )
                />,
              persons
            )
          )
        )
      )
      (
        ReasonReact.arrayToElement(
          Array.of_list(
            List.mapi(
              (idx, prize: Prize.prize) =>
                <Prize
                  key=(string_of_int(idx))
                  prize
                  beingRaffled=(isSelected(prizeInRaffle, idx))
                />,
              prizes
            )
          )
        )
      )
    </div>;
  }
};