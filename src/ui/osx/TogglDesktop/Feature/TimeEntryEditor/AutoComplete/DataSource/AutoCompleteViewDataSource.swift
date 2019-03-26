//
//  AutoCompleteViewDataSource.swift
//  TogglDesktop
//
//  Created by Nghia Tran on 3/25/19.
//  Copyright © 2019 Alari. All rights reserved.
//

import Foundation

class AutoCompleteViewDataSource: NSObject {

    // MARK: Variables
    private let maxHeight: CGFloat = 600.0
    private(set) var items: [Any] = []
    private var autoCompleteView: AutoCompleteView!
    var tableView: NSTableView {
        return autoCompleteView.tableView
    }

    // MARK: Init

    init(items: [Any], updateNotificationName: Notification.Name) {
        super.init()
        self.items = items
        NotificationCenter.default.addObserver(self,
                                               selector: #selector(self.receiveDataSourceNotifiation(_:)),
                                               name: updateNotificationName,
                                               object: nil)
    }

    deinit {
        NotificationCenter.default.removeObserver(self)
    }

    // MARK: Public

    func prepare(_ autoCompleteView: AutoCompleteView) {
        self.autoCompleteView = autoCompleteView
        registerCustomeCells()
        tableView.delegate = self
        tableView.dataSource = self
    }

    func registerCustomeCells() {
        // Should override
    }

    func render(with items: [Any]) {
        self.items = items
        tableView.reloadData()
        sizeToFit()
    }

    func filter(with text: String) {
        // Should override
    }

    @objc func receiveDataSourceNotifiation(_ noti: Notification) {
        guard let items = noti.object as? [Any] else {
            return
        }
        render(with: items)
    }

    private func sizeToFit() {
        // Get total height of all cells
        let totalHeight = items.enumerated().reduce(into: 0.0) { (height, item) in
            return height += tableView(tableView, heightOfRow: item.offset)
        }

        // Get suitable height
        // 0 <= height <= maxHeight
        var suitableHeight = CGFloat.minimum(CGFloat.maximum(0, totalHeight), maxHeight)

        // Padding
        if let scrollView = tableView.enclosingScrollView {
            suitableHeight += scrollView.contentInsets.bottom + scrollView.contentInsets.top
        }

        autoCompleteView.update(height: suitableHeight)
    }
}

extension AutoCompleteViewDataSource: NSTableViewDataSource, NSTableViewDelegate {

    func numberOfRows(in tableView: NSTableView) -> Int {
        return items.count
    }

    func tableView(_ tableView: NSTableView, viewFor tableColumn: NSTableColumn?, row: Int) -> NSView? {
        return nil
    }

    func tableView(_ tableView: NSTableView, heightOfRow row: Int) -> CGFloat {
        return 44.0
    }

    func tableView(_ tableView: NSTableView, shouldSelectRow row: Int) -> Bool {
        return true
    }
}
