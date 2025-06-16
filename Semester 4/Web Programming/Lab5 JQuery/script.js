$(document).ready(function () {
    for (let i = 0; i < 5; i++) {
        addReadOnlyRow([`R${i + 1}C1`, `R${i + 1}C2`, `R${i + 1}C3`, `R${i + 1}C4`, `R${i + 1}C5`]);
    }

    function addReadOnlyRow(data = ["", "", "", "", ""]) {
        const $row = $("<tr>");
        const $leftBtn = $('<td><button class="deleteBtn">Delete</button></td>');
        const $rightBtn = $('<td><button class="addBtn">Add Editable</button></td>');

        $row.append($leftBtn);
        for (let i = 0; i < 5; i++) {
            $row.append(`<td>${data[i]}</td>`);
        }
        $row.append($rightBtn);
        $("#myTable tbody").append($row);
    }

    function addEditableRow(afterRow) {
        const $row = $("<tr>");
        const $leftBtn = $('<td><button class="deleteBtn">Delete</button></td>');
        const $rightBtn = $('<td><button class="addBtn">Add Editable</button></td>');

        $row.append($leftBtn);
        for (let i = 0; i < 5; i++) {
            $row.append(`<td><input type="text" /></td>`);
        }
        $row.append($rightBtn);
        $row.insertAfter(afterRow);

        $row.find("input").on("blur", function () {
            const allFilled = $row.find("input").toArray().every(input => $(input).val().trim() !== "");
            if (allFilled) {
                $row.find("td").each(function () {
                    const $td = $(this);
                    const $input = $td.find("input");
                    if ($input.length) {
                        $td.text($input.val());
                    }
                });
            }
        });
    }

    $("#myTable").on("click", ".deleteBtn", function () {
        const $row = $(this).closest("tr");
        $row.remove();
    });

    $("#myTable").on("click", ".addBtn", function () {
        const $row = $(this).closest("tr");
        addEditableRow($row);
    });

    $('#addRowBelowEach').click(function () {
        $("#myTable tbody tr").each(function () {
            const $row = $(this);
            addEditableRow($row);
        });
    });
});