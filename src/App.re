let prizes: list(Prize.prize) = [
  {name: "A subscription"},
  {name: "Some other thing"},
  {name: "more stuff"}
];

type action =
  | PersonSelected(int, bool);

type state = {
  persons: list(Person.person),
  inRaffle: bool,
  numberSelected: int
};

let component = ReasonReact.reducerComponent("App");

let fibonacci = (prev: int, prev_prev: int) => prev + prev_prev;

let makeLoop = self => {
  let rec loop = (state, time, prev_time) => {
    let tmp = ref(state);
    let chosen = Random.int(List.length(self.ReasonReact.state.persons));
    let next_time = fibonacci(time, prev_time);
    let finished = time > 60;
    self.ReasonReact.send(PersonSelected(chosen, finished));
    switch finished {
    | false =>
      Window.setTimeout(() => loop(tmp^, next_time, time), next_time * 20)
      |> ignore
    | true => ()
    };
  };
  loop(self.ReasonReact.state, 1, 0);
};

let handleClick = (_event, self) => makeLoop(self);

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
    inRaffle: false,
    numberSelected: 9
  },
  reducer: (action, state) =>
    switch action {
    | PersonSelected(id, finished) =>
      ReasonReact.Update({...state, numberSelected: id, inRaffle: ! finished})
    },
  render: self =>
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
                  selected=(self.state.numberSelected === person.id)
                  inRaffle=self.state.inRaffle
                  key=person.fullName
                />,
              self.state.persons
            )
          )
        )
      )
    </div>
};