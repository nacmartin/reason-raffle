type person = {
  fullName: string,
  id: int
};

type personColor =
  | Default
  | AlreadySelected
  | Selected
  | InRaffle;

let color = status =>
  switch status {
  | Default => "#aaa"
  | AlreadySelected => "#f00"
  | Selected => "#0f0"
  | InRaffle => "#00f"
  };

let component = ReasonReact.statelessComponent("Person");

let getBg = (selected: bool, inRaffle: bool, alreadySelected: bool) =>
  if (selected) {
    if (inRaffle) {
      color(InRaffle);
    } else {
      color(Selected);
    };
  } else if (alreadySelected) {
    color(AlreadySelected);
  } else {
    color(Default);
  };

let make =
    (
      ~person: person,
      ~selected: bool,
      ~inRaffle: bool,
      ~alreadySelected: bool,
      _children
    ) => {
  ...component,
  render: _self =>
    <div
      style=(
        ReactDOMRe.Style.make(
          ~color="#444444",
          ~fontSize="42px",
          ~backgroundColor=getBg(selected, inRaffle, alreadySelected),
          ()
        )
      )>
      (ReasonReact.stringToElement(person.fullName))
    </div>
};