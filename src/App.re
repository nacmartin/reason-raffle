let prizes: list(Prize.prize) = [
  {name: "A subscription"},
  {name: "Some other thing"},
  {name: "more stuff"}
];

type action =
  | Click;

type state = {
  persons: list(Person.person),
  inRaffle: bool,
  numberSelected: int
};

let component = ReasonReact.reducerComponent("App");

let handleClick = (_event, _self) => Js.log("clicked!");

let make = _children => {
  ...component,
  initialState: () => {
    persons: [{fullName: "John", id: 0}, {fullName: "Por", id: 1}],
    inRaffle: false,
    numberSelected: 9
  },
  reducer: (action, state) =>
    switch action {
    | Click => ReasonReact.Update({...state, inRaffle: true})
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
                  key=person.fullName
                />,
              self.state.persons
            )
          )
        )
      )
    </div>
};