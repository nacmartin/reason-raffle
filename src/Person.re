type person = {
  fullName: string,
  id: int
};

let component = ReasonReact.statelessComponent("Person");

let getBg = (selected: bool, inRaffle: bool) =>
  if (selected) {
    if (inRaffle) {"#f00"} else {"#00f"};
  } else {
    "#0f0";
  };

let make = (~person: person, ~selected: bool, ~inRaffle: bool, _children) => {
  ...component,
  render: _self =>
    <div
      style=(
        ReactDOMRe.Style.make(
          ~color="#444444",
          ~fontSize="68px",
          ~backgroundColor=getBg(selected, inRaffle),
          ()
        )
      )>
      (ReasonReact.stringToElement(person.fullName))
    </div>
};